# 8puzzle solver #

[Programming assignment 4](http://coursera.cs.princeton.edu/algs4/assignments/8puzzle.html)

[Checklist](http://coursera.cs.princeton.edu/algs4/checklists/8puzzle.html)

### To do list ###
* I probably have to write my own minimum priority queue class - done
* Implement iterator for MinPQ - done. `begin` and `end` goes from 1 to N+1, instead of 0 to N.
* Implement copy constructor and assignment operator for MinPQ 
* Figure out how to implement equivalent of an iterable interface in C++ - just using Deque
* I think I can make this way more efficient by having Solver::Node inherit Board! - done.
* The way to go is to have the MinPQ be made of pointers to Nodes, instead of actual Nodes. That way, you don't have to move shit around with copying and assigning Nodes (which can be a huge pain in the butt). With pointers, you can just sort by pointer (using a custom comparator that accesses the appropriate member), and move pointers around. Much easier. Basically, because all the Nodes are `new` allocated, it makes it a lot easier to keep track of everything if nothing moves around.

### Things I've learned ###
* In Java, you can set an element of an array to null to help with garbage collection. Apparently, you can't do this in C++ because dynamically allocated memory is allocated as a single region, which can only be freed as a whole, not in parts. See [Link](http://stackoverflow.com/questions/12810928/free-array-element-in-c)
* To read files from the program (instead of putting them as command line arguments), put the files/folders in the same folder as the source file.
* For copy assignment operator, to check for self copying, use (&that == this), not (*this == that)
* If you're going to overload operators of a derived class, you have to do all or none. If you you do none, you can use the base class' operators. If you do one, you have to do all of them.
* Man, I've learned so much. Let's see... 
* Memory leaks: you have to delete everything you made with `new`. For this project, the easiest way was to keep track of all the new nodes that `neighbor` produced, and then delete it all at the end.
* Custom comparator class wasn't bad. Just need to make sure you overload the `operator()` function, and then in your template class declaration do a default thing like `template <class T, Comp = c<T>>`. Define `c` as your default comparator, and then your custom comparator in whatever class.
* Deques are super useful. And it's cool that I implemented it myself.
* Learned about upcasting a derived class in order to overload the output operator. To upcast Node, `const Board* b = &that`, and then you can call `output << b`.

### Notes about git ###
* use `git revert <commit>` to move back to an older commit
* use `git fetch origin <commit>` to fetch a remote commit that you want
* use `git checkout FETCH_HEAD` after the fetch to switch to that branch
* use `git branch -b <name>` to give that branch a name
* use `git reset --hard <commit>` to move HEAD to the current commit and basically deletes everything afterwards
* use `git merge --strategy=ours master` to merge master into ours, but keeping ours
* use `git checkout master` and `git merge <name>` to update master to the correct place
* use `git branch -d <name>` to delete branch

I still need to figure out how to resolve conflicts (i.e. when I forget to push something from home or office. I think the right way to do it is to `git checkout --ours filename.c` or `git checkout --theirs filename.c` depending on which one you want, and then `git add filename.c` and `git commit -m "using theirs/ours"` to pick which one to use...