This solution works, but there are a couple of shortcuts that I took based on the nature of this Advent of Code problem.

The first issue I have is that this does nothing to validate the input data and assumes that all lines can be split evenly in two, and that the total number of lines can be divided evenly by 3.
The second issue is that there is an assumption made that we will always find one and only one character in common between the different inputs.
In production code I would spend more time error handling these issues because real life input data is generally not always this tidy.
