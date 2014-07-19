# 8puzzle solver #

[Programming assignment 4](http://coursera.cs.princeton.edu/algs4/assignments/8puzzle.html)

[Checklist](http://coursera.cs.princeton.edu/algs4/checklists/8puzzle.html)

### To do list ###
* I probably have to write my own minimum priority queue class - mostly done
* Implement iterator for MinPQ
* Implement copy constructor and assignment operator for MinPQ
* Figure out how to implement equivalent of an iterable interface in C++ - just using Deque
* I think I can make this way more efficient by having Solver::Node inherit Board!

### Things I've learned ###
* In Java, you can set an element of an array to null to help with garbage collection. Apparently, you can't do this in C++ because dynamically allocated memory is allocated as a single region, which can only be freed as a whole, not in parts. See [Link](http://stackoverflow.com/questions/12810928/free-array-element-in-c)
* To read files from the program (instead of putting them as command line arguments), put the files/folders in the same folder as the source file.
* For copy assignment operator, to check for self copying, use (&that == this), not (*this == that)

### Notes about git ###
* use `git revert <commit>` to move back to an older commit
* use `git fetch origin <commit>` to fetch a remote commit that you want
* use `git checkout FETCH_HEAD` after the fetch to switch to that branch
* use `git branch -b <name>` to give that branch a name
* use `git reset --hard <commit>` to move HEAD to the current commit and basically deletes everything afterwards
* use `git merge --strategy=ours master` to merge master into ours, but keeping ours
* use `git checkout master` and `git merge <name>` to update master to the correct place

I still need to figure out how to resolve conflicts (i.e. when I forget to push something from home or office. I think the right way to do it is to `git checkout --ours filename.c` or `git checkout --theirs filename.c` depending on which one you want, and then `git add filename.c` and `git commit -m "using theirs/ours"` to pick which one to use...