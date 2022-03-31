clear all ;
close all ;
clc ;

% Horn & Schunck


fileU = fopen('U.txt','rt');
fileV = fopen('V.txt','rt');

U = load('U.txt');
V = load('V.txt');
taille=size(U).';


img = imread('image1.bmp');
img2 = imread('image2.bmp');
fileU = fopen('U.txt','rt');
fileV = fopen('V.txt','rt');

U = load('U.txt');
V = load('V.txt');
taille=size(U).';


img = imread('image1.bmp');
img2 = imread('image2.bmp');

figure(1)
subplot(1,3,1);
image(img);axis image;
title('HS instant t');
subplot(1,3,2);
image(img2);axis image;
title('HS instant t+1');
hold on
quiver(U,V,'r');
subplot(1,3,3);
quiver(U,V,'r');axis image;




% MULTI RESOLUTION
fileU1 = fopen('U_MultiRes.txt','rt');
fileV1 = fopen('V_MultiRes.txt','rt');

U1 = load('U_MultiRes.txt');
V1 = load('V_MultiRes.txt');
taille=size(U1).';


img = imread('image1.bmp');
img2 = imread('image2.bmp');

figure(2)

subplot(1,3,1);
image(img);axis image;
title('MR instant t');
subplot(1,3,2);
image(img2);axis image;
title('MR instant t+1');
hold on
quiver(U1,V1,'r');
subplot(1,3,3);
quiver(U1,V1,'r');axis image;



% Filtre De Gauss
fileU2 = fopen('U_FILTRE_MultiRes.txt','rt');
fileV2 = fopen('V_FILTRE_MultiRes.txt','rt');

U2 = load('U_FILTRE_MultiRes.txt');
V2 = load('V_FILTRE_MultiRes.txt');
taille=size(U2).';


img = imread('image1.bmp');
img2 = imread('image2.bmp');

figure(3)

subplot(1,3,1);
image(img);axis image;
title('FG instant t');
subplot(1,3,2);
image(img2);axis image;
title('FG instant t+1');
hold on
quiver(U2,V2,'r');
subplot(1,3,3);
quiver(U2,V2,'r');axis image;