data=importdata("injection.dat");
xgrid=data(1:end,1);
xxz=data(1:end,2);
yxz=data(1:end,3);
zxz=data(1:end,4);
figure('units','normalized','outerposition',[0 0 1 1])
plot(xgrid,xxz,'-r+',xgrid,yxz,'-kp',xgrid,zxz,'-m+','LineWidth',2)
legend("xxz","yxz","zxz")
xlabel("Photon Energy(ev)");
ylabel("Susceptibility(A/V^2)")
set(gca,"FontSize",26)
saveas(gcf,'BTO.eps','epsc')
