function  y = qei_sim(u1)
    in = u1;
    out = u1;
    if in > %pi then
        out =  modulo(in-%pi, 2*%pi) - %pi;
    end
    if in < -%pi then
        out =  modulo(in+%pi, 2*%pi) + %pi;
    end

    y = out*1/%pi;


endfunction
