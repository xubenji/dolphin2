#Add your remote compiler server
IPaddress=111.229.221.155

rsync -rvlt --exclude '.git' ./ root@$IPaddress:/root/os
ssh root@$IPaddress "cd os; make"
scp root@$IPaddress:/root/os/kernel8.img ./

#qemu-system-aarch64 -M raspi2 -kernel kernel8.img

