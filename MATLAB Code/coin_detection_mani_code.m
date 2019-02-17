clear all;
close all;

% Start the webcam
cam = webcam(1);
img = snapshot(cam);
imshow(img);

% This is where and what your image will be saved
%counter  = 1;
baseDir  = '/home/prateek/Documents/MATLAB/Minor Project Code/';
baseName = 'image';
newName = fullfile(baseDir, sprintf('%s.jpg', baseName));
%newName  = [baseDir baseName '.jpg'];
%while exist(newName,'file')
    %counter = counter + 1;
    %newName = [baseDir baseName num2str(counter) '.jpg'];
%end    
imwrite(img, newName);

%savepath = '/home/prateek/Documents/MATLAB/Minor Project Code';
%nametemplate = 'img.jpg';  

rgb = imread('/home/prateek/Documents/MATLAB/Minor Project Code/image.jpg');
figure
imshow(rgb);

%d = imdistline;
%delete(d);

%Image Conversion, Thresholding and creating circles around the coins
gray_image = rgb2gray(rgb);
imshow(gray_image);
[centres, radii] = imfindcircles(rgb, [75 110], 'ObjectPolarity', 'dark', 'Sensitivity', 0.979);
imshow(rgb)
h = viscircles(centres, radii);
length(centres);

% Finding the radii of the coins
r = round(radii(1))+1;
x = round(centres(1,1))-r;
y = round(centres(1,2))-r;
d = 2*r;
I = imcrop(rgb, [x y d d]);
figure
imshow(I)
title(['Radius: ' num2str(radii(1)) 'px']);
value = radiif(radii(1));
disp(value);

% Arduino Communication
arduino=serial('/dev/ttyACM0','BaudRate',9600);
fopen(arduino);
fprintf(arduino, '%d', value);
fclose(arduino);

clear('cam');