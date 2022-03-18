#!/bin/bash

compile_std() {
	clang++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address -DTEST_STD main.cpp -o std_test
}

compile_ft() {
	clang++ -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address main.cpp -o ft_test
}


echo "Compiling versions"
compile_std
compile_ft

seed=$(( RANDOM ))
echo "Seed is $seed"
echo ""

echo "Testing STD"
start=$SECONDS
./std_test $seed > std_output.txt
end=$SECONDS
duration=$(( end - start ))
echo "STD took $duration seconds"
echo ""

echo "Testing FT timings:"
start=$SECONDS
./ft_test $seed > ft_output.txt
end=$SECONDS
duration=$(( end - start ))
echo "FT took $duration seconds"
echo ""

if diff ft_output.txt std_output.txt > /dev/null;then
    echo "No output differences";
else 
	diff ft_output.txt std_output.txt > /dev/null;
    echo "Output differ";
fi


rm std_test
rm ft_test

rm ft_output.txt
rm std_output.txt