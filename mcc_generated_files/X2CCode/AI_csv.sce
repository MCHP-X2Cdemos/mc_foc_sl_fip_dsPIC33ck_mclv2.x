
function createCSV()
    temp = [];
    for i = 1:fix(length(var_name.Data.Channel1.Values)/columns)
        for j = 1:columns
            temp(i,j) = var_name.Data.Channel1.Values(i+j);
        end;
    end
    csvWrite(temp,csv_name)
    plot(var_name.Data.TimeStamp,var_name.Data.Channel1.Values);
endfunction
    
    columns = 32;
    figure(101);
     a=gca();

    filename = 'normalC';
    exec('normalC.sce'); 
    var_name = normalC_var;
    csv_name = 'normalC.csv';
    createCSV();
        
    filename = 'bearing_0_6__0_1C';
    exec('bearing_0_6__0_1C.sce'); 
    var_name = bearing_0_6__0_1C_var;
    csv_name = 'bearing_0_6__0_1C.csv';
    createCSV();
    
    filename = 'unbalance_0_4__0_4C';
    exec('unbalance_0_4__0_4C.sce'); 
    var_name = unbalance_0_4__0_4C_var;
    csv_name = 'unbalance_0_4__0_4C.csv';
    createCSV();
    
    filename = 'traingle_1_2__0_2C';
    exec('traingle_1_2__0_2C.sce'); 
    var_name = traingle_1_2__0_2C_var;
    csv_name = 'traingle_1_2__0_2C.csv';
    createCSV();    
    
    filename = 'ramp_1_2__0_2C';
    exec('ramp_1_2__0_2C.sce'); 
    var_name = ramp_1_2__0_2C_var;
    csv_name = 'ramp_1_2__0_2C.csv';
    createCSV();  
    
    figure(102);
 
    plot(normalC_var.Data.TimeStamp,[normalC_var.Data.Channel1.Values; bearing_0_6__0_1C_var.Data.Channel1.Values; unbalance_0_4__0_4C_var.Data.Channel1.Values; traingle_1_2__0_2C_var.Data.Channel1.Values; ramp_1_2__0_2C_var.Data.Channel1.Values]);
    xtitle('measured current');
    a.y_label.text ="current";
    a.x_label.text ="time";
    
    figure(103);
    subplot(2,4,1);
    plot(normalC_var.Data.TimeStamp,normalC_var.Data.Channel1.Values);

    subplot(2,4,5);
    plot(normalC_var.Data.TimeStamp,bearing_0_6__0_1C_var.Data.Channel1.Values);    

    subplot(2,4,6);
    plot(normalC_var.Data.TimeStamp,unbalance_0_4__0_4C_var.Data.Channel1.Values);    
    
    subplot(2,4,7);
    plot(normalC_var.Data.TimeStamp,traingle_1_2__0_2C_var.Data.Channel1.Values);    

    subplot(2,4,8);
    plot(normalC_var.Data.TimeStamp,ramp_1_2__0_2C_var.Data.Channel1.Values);        
    
    
    
    
    
