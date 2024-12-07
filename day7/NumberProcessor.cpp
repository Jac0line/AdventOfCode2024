#include "NumberProcessor.h"
#include <c++/10/bits/stream_iterator.h>

std::vector<long long int> NumberProcessor::parseLine(const std::string& line, const std::string& delimiter) {
    std::vector<long long int> numbers;
    std::istringstream stream(line);
    long long int number;

    while (stream >> number) {
        std::cout << number << std::endl;
        numbers.push_back(number);
    }
    return numbers;
}

bool NumberProcessor::readInput(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        
        std::string delimiter = ":";
        std::string sum = line.substr(0, line.find(delimiter));
        std::string numbers_string = line.substr(line.find(delimiter)+2);
        std::cout << sum << std::endl;

        std::vector<long long int> numbers = parseLine(numbers_string, " ");
        all_numbers.push_back(numbers);
        all_sums.push_back(stoll(sum));
    }

    inputFile.close();
    return true;
}

long long int NumberProcessor::CalcTotalCalibrationResult(bool part2)
{
    std::cout << "CalcTotalCalibrationResult" <<std::endl;
    long long int result = 0;
    long long int nr_of_lines = all_numbers.size();
    for(long long int i = 0; i < nr_of_lines; ++i)
    {
        std::vector<long long int> input;
        std::vector<long long int> output;
        std::vector<long long int> numbers_line = all_numbers[i];
        long long int sum = all_sums[i];
        std::cout<< "numbers_line.size()" << numbers_line.size() << std::endl;
        for(const auto& number : numbers_line)
        {
            std::cout << number <<std::endl;
            if(input.empty())
            {
                output.push_back(number);                
            } else {
                for(const auto& inputNumber : input) {
                    output.push_back(inputNumber * number);
                    output.push_back(inputNumber + number);
                    if(part2)
                    {
                        output.push_back(std::stoll(std::to_string(inputNumber)+std::to_string(number)));
                    }
                }
            }
            input.clear();
            input.resize(output.size()); 
        
            // Move elements from output to input 
            for (size_t i = 0; i < output.size(); ++i) { 
                input[i] = std::move(output[i]); 
            } 
        
            // Optionally clear the output vector if you want to empty it 
            output.clear(); // Now output is empty 
        }
        for(long long int i = 0; i<input.size(); ++i)
        {
            if(sum == input[i])
            {
                std::cout << "Adding to result:" << sum << std::endl;
                result += sum;
                break;
            }
        }
        input.clear();
    }

    return result;
}