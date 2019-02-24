classdef Sensor_reading
    %SENSOR_READING Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        t0_idx % launch time
        t0 % launch time
        data % raw data from file
        
        idx_type = {'id','time','pressure','temp','altitude', ...
            'acc x', 'acc y', 'acc z', ...
            'gyro x', 'gyro y', 'gyro z', ...
            'mag x', 'mag y', 'mag z'} % different type of data available
        idx_unit = {'#','ms','Pa','deg C', 'm', ...
            'm/s2', 'm/s2', 'm/s2', ...
            'rad/s', 'rad/s', 'rad/s', ...
            'uT', 'uT', 'uT'} % units of the data in table
    end
    
    methods
        function obj = Sensor_reading(filename, start_idx)
            %SENSOR_READING Construct an instance of this class
            %   - filename name of the file to import
            %   - only consider data starting from start_idx (0 for all
            %   data)
            obj.data = csvread(filename, 1+start_idx, 0);
        end
        
        function obj = set_t0(obj, data_type, threshold, timeout)
            %SET_T0 Automatically detect launch time
            %   - data_type see idx_type
            %   - threshold min val of the data_type
            %   - timeout min amount of time for which the data if above
            %   threshold
            ut = Utilities;
            idx_data = ut.id_strInCell(obj.idx_type, data_type);
            idx_t    = ut.id_strInCell(obj.idx_type, 'time');
            
            obj.t0_idx = obj.data(1,idx_t); % set first value to default
            
            [n_max, ~] = size(obj.data);
            detected = 0;

            for ii=1:n_max
                if abs(obj.data(ii, idx_data)) < threshold %% not above thresold
                    detected = 0;
                else
                    if detected == 0 % first time above threshold
                        detected = 1;
                        t_detected = obj.data(ii,idx_t);
                        t_detected_idx = ii;
                    end
                    
                    if (obj.data(ii,idx_t) - t_detected)>timeout % detected for long enough
                        obj.t0     = t_detected;
                        obj.t0_idx = t_detected_idx;
                        return
                    end
                end
            end
        end
        
        function plot_types(obj, types)
            ut = Utilities;
            idx_t    = ut.id_strInCell(obj.idx_type, 'time');
            
            t = (obj.data(:,idx_t) - obj.t0)/1e3;
            
            for type=types
                idx_data = ut.id_strInCell(obj.idx_type, type);
                plot(t, obj.data(:, idx_data));
                hold on;
            end
            
            legend(types);
            xlabel('t [s]')
        end
    end
end

