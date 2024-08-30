import fractions

def process_number(value):
    if value == 0:
        return "scalar(0)"
    
    negative = False
    if value < 0:
        negative = True
        value = abs(value)
    
    # Convert to fraction
    fraction = fractions.Fraction(value).limit_denominator()
    numerator = fraction.numerator
    denominator = fraction.denominator

    # Generate the output string
    if denominator == 1:
        result = f"scalar({numerator})"
    else:
        result = f"scalar({numerator})/scalar({denominator})"
    
    if negative:
        result = "-" + result
    
    return result

# Example input list
numbers = [1/8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3/8, 0, 0, 0, 0, 0, 3/8, 0, 0, 1/8, \
1/8, 1/8, 0, 0, 0, 0, 0, 0, 0, 0, 1/4, 1/4, 0, 0, 0, 0, 1/8, 1/8, 0, \
0,1/8, 1/4, 1/8, 0, 0, 0, 0, 0, 0, 0, 1/8, 1/4, 1/8, 0, 0, 0, 0, \
0, 0, 0,1/8, 3/8, 3/8, 1/8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
0, 0, 0,1/8, 0, 0, 0, 1/8, 0, 0, 0, 0, 0, 1/4, 0, 0, 1/4, 0, 0, \
1/8, 0, 1/8, 0,1/8, 1/8, 0, 0, 1/8, 1/8, 0, 0, 0, 0, 1/8, 1/8, 0, \
1/8, 1/8, 0, 0, 0, 0, 0,1/8, 1/4, 1/8, 0, 1/8, 1/4, 1/8, 0, 0, 0, \
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1/8, 0, 0, 0, 1/4, 0, 0, 1/8, 0, 0, \
1/8, 0, 0, 1/4, 0, 1/8, 0, 0, 0, 0,1/8, 1/8, 0, 0, 1/4, 1/4, 0, \
1/8, 1/8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1/8, 0, 0, 0, 3/8, 0, 0, \
3/8, 0, 1/8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 1/8, 0, 0, \
0, 0, 0, 1/8, 0, 0, 1/4, 0, 0, 1/4, 0, 1/8, 1/8,0, 0, 0, 0, 1/8, \
1/8, 0, 0, 0, 0, 1/8, 1/8, 0, 1/8, 1/8, 0, 1/8, 1/8, 0, 0,0, 0, 0, \
0, 1/8, 1/4, 1/8, 0, 0, 0, 1/8, 1/4, 1/8, 0, 0, 0, 0, 0, 0, 0,0, \
0, 0, 0, 1/8, 0, 0, 1/8, 0, 0, 1/8, 0, 0, 1/4, 0, 1/8, 1/8, 0, 1/8, \
0,0, 0, 0, 0, 1/8, 1/8, 0, 1/8, 1/8, 0, 1/8, 1/8, 0, 1/8, 1/8, 0, \
0, 0, 0, 0,0, 0, 0, 0, 1/8, 0, 0, 1/4, 0, 1/8, 1/8, 0, 0, 1/4, 0, \
1/8, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 1/8, 0, 0, 0, 0, 0, 1/4, 0, \
1/8, 1/8, 0, 1/4, 1/8,0, 0, 0, 0, 0, 0, 0, 1/8, 1/8, 0, 0, 0, 0, \
1/4, 1/4, 0, 1/8, 1/8, 0, 0,0, 0, 0, 0, 0, 0, 0, 1/8, 0, 1/8, 0, \
0, 0, 1/4, 0, 1/4, 1/8, 0, 1/8, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 1/8, \
0, 0, 0, 0, 0, 3/8, 0, 0, 3/8, 1/8]
# Processing numbers and formatting the output
output = []
for i, number in enumerate(numbers):
    if i % 20 == 0:
        output.append(f"// Row {i // 20 + 1}\n")
    
    result = process_number(number)
    output.append(result)
    
    if i % 5 != 4:
        output.append(", ")
    else:
        output.append(",\n")
    

output_text = "".join(output)

print(output_text)
