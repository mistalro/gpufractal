for file in *.h *.cpp 
do
echo $file
sed -e "s/ofstream/ostream/g" < $file > temp
mv temp $file
done
