# MemComJournal
This is for the paper published on TPDS, Partitioning Tree-Shaped Task Graphs for Distributed Platforms With Limited Memory. All codes are here. And you can download the trees from
https://drive.google.com/file/d/1xarXdknzWO_e76gL9_pRAKPICbLQKnfR/view?usp=sharing
Each text file represents a tree. In the file, each line represents a node. Columns represent attributes, which are node_id, its ancestor's ide, node_memory_weight, node_makespan_weight, weight_of_the_edge_to_the_ancestor.
or
https://graal.ens-lyon.fr/~lmarchal/data/real_trees_nf.zip
Dataset from this link include not noly trees used in the paper but also some other trees. They share the same format as the one above, except colunms represent id_node, id_parent_node, memory_size_of_task, memory_size_of_outgoing_edge, processing_time_of_node.

If you have any problem, please feel free to contact the authors. My email is gouchangjiang@gmail.com.

----------------------------------How to run the code to get the simulation results---------------------------
Just clone the code onto your computer,
  git clone https://github.com/gouchangjiang/MemComJournal.git
then goto the MemComJournal directory,
  cd path/to/MemComJournal
then compile it by
  make
then goto the example directory,
  cd ./example
then compile it by
  make
now if it succeed, you can see an executeble file named call-heuristics, see you put the tree at the subdirectory ./realTrees/, and in this subdirectory, you have a txt file which list the name of all tree files, say it's treesList.txt. Then the command to run a specific algorithm with a given computation to communication ratio (CCR), number of processors is 
./call-heuristics -s -c 0.001 -n 100 -d ./realTrees/ treesList.txt >> ../../result/result_split_1
Here, the CCR is given as -c 0.001, the number of processors is given as -n 100, and the algorithm is given as -s, which means heuristic SplitSubtrees used in the first stage. The result is then saved in the file result_split_1. Other options to set which heuristic to use in stage 1 are -i ImprovedSplit; -a AvoidChain. For heuristics to use in stage 2, you can set the option -f FirstFit; -e Immediately; -l LargestFirst.

The odd lines of the results list the edegs broken, and even lines list "TreeName NPR CCR MemoryConstraint AmountSubtrees AmountProcessors Makespan Stage1 Stage2 Stage3 TimeConsuming" info of each run. You can filt the edges broken, and save it as a seperate files by a python or R script.

