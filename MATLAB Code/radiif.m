% Find the value of the coin by passing the radius value
function f = radiif(rad)

if rad>=75 && rad<=84
    f = 5;
    
elseif rad>=91.01 && rad<=106
    f = 2;
    
elseif rad>=84.01 && rad<=91
    f = 1;
    
end