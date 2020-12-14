x1=rand(201,1);
x2=rand(201,1);
x3=rand(201,1);
x4=rand(201,1);
x5=rand(201,1);
x6=rand(201,1);
x7=rand(201,1);
x8=rand(201,1);
x9=rand(201,1);
x10=rand(201,1);
for i=1:201
    if rand(1,1)>0.5
        x11(i)=1;
    else
        x11(i)=0;
    end
end


for i=1:1:201
    data(i,1)=x1(i);
end
for i=1:1:201
    data(i,2)=x2(i);
end
for i=1:1:201
    data(i,3) =x3(i);
end
for j=1:1:201
    data(j,4) =x4(j);
end
for i=1:1:201
    data(i,5) =x5(i);
end
for j=1:1:201
    data(j,6) =x6(j);
end
for i=1:1:201
    data(i,7) =x7(i);
end
for j=1:1:201
    data(j,8) =x8(j);
end
for i=1:1:201
    data(i,9) =x9(i);
end
for j=1:1:201
    data(j,10) =x10(j);
end
for j=1:1:201
    data(j,11) =x11(j);
end

fid=fopen(['C:/Users/zkcc2/Desktop/','data.txt'],'w');%写入文件路径
[r,c]=size(data);            % 得到矩阵的行数和列数 
for i=1:r  
    for j=1:c  
        fprintf(fid,'%f ',data(i,j));  
    end
    fprintf(fid,'\r\n'); 
end
fclose(fid);
