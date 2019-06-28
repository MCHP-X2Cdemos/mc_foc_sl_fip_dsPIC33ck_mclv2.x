function  y = qei_sim2(u1)
    in = u1;
    out = u1;
    
    out = modulo(in, 2*%pi);
    out = out * (500/%pi);
    
    y = out;
endfunction
