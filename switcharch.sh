if [ "$1" == "x86" ]
    then
sed -i "s/arm/x86/g" config.mk
sed -i "s/arm/amd64/g" ./.vscode/launch.json
make clean

if [ "$2" == "d" ]
then
make $2
else 
make run
fi

elif [ "$1" == "arm" ]
    then
sed -i "s/x86/arm/g" config.mk
sed -i "s/amd64/arm/g" ./.vscode/launch.json
make clean

if [ "$2" == "d" ]
then
make $2
else 
make run
fi

else 

if [ "$2" == "d" ]
then
make $2
else 
make run
fi

fi