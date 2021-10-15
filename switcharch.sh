#转化平台，想要转为x86平台，就输入
#bash switcharch.sh x86
#转为arm平台请输入
#bash switcharch.sh arm

if [ "$1" == "x86" ]
    then
sed -i "s/arm/x86/g" config.mk
sed -i "s/arm/amd64/g" ./.vscode/launch.json
make clean

make $2

elif [ "$1" == "arm" ]
    then
sed -i "s/x86/arm/g" config.mk
sed -i "s/amd64/arm/g" ./.vscode/launch.json
make clean

make $2

else 

make $2

fi