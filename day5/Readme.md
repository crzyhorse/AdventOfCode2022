I don't like this code, mainly because of what I did to use the stacks for both parts. I ended up returning a pointer to an array of std::deque
and then using std::copy to duplicate it for part 2. I think in this case, more elegant would have been just to have two seperate .CPP files as I've seen some do. 

It also might have been better to read the entire file line by line and just use Regex to parse, having only one function. Just have a regex for
the stacks, and another for the moves. There is something nice about the simplicity I ended up with though, so I'm not sure.

Anyway it all works. 
