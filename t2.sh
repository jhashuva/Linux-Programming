select c in cp mkdir cd
do 
case $c in
cp) echo "cp is invoked";;
mkdir) echo "mkdir is invoked";;
cd) echo "cd is invoked";;
*) break;;
esac
done
