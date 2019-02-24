%% Load data
start_idx = 50;
log = Sensor_reading('SENSORS.TXT', start_idx);

log = log.set_t0('acc y', 2, 500);
%% Plot
figure;
log.plot_types({'acc x', 'acc y', 'acc z'})
xlim([-10, 150]);

figure;
log.plot_types({'mag x', 'mag y', 'mag z'})
xlim([-10, 150]);

figure;
log.plot_types({'gyro x', 'gyro y', 'gyro z'})
xlim([-10, 150]);


