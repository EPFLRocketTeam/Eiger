classdef Utilities
    %UTILITIES Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
    end
    
    methods
        function idx = id_strInCell(~, cell, str)
            idx = find(strcmp(cell, str),1);
        end
    end
    
end

