// simulation sequence+stage2+splitAgain/Merge
//  Created by changjiang GOU on 10/05/2018.
//  Copyright © 2018 Changjiang GOU. All rights reserved.

// #include <iostream>
// #include <fstream>
// #include <string>
// #include <math.h>
// #include <stdlib.h>
// #include "lib-io-tree.h"
// #include "heuristics.h"
//
// int main(int argc, const char * argv[]) {
//    int tree_size=0;
//    int *prnts;
//    double *ewghts, *spacewghts, *timewghts;
//    int * chstart,*chend,*children;
//    int root;
//    string dir=argv[1];
//    string treename;
//    double makespan;
//    double maxoutd;
//    //double CCRs[] = {1, 0.1, 0.001};//communication to computation
//    double CCR=atof(argv[3]);
//    //double NPR[] = {100000, 10000, 1000};//ratio of nodes' amount to processors
//    double NPR=atof(argv[4]);
//    clock_t time;
//
//    unsigned int number_subtrees;
//    unsigned int num_processors;
//    int memory_constraint_options[3]={1,2,3};
//    int memory_constraint;
//    double memorySize, minMem;
//    uint64_t count;
//    string stage2heuristic;
//
//    cout.precision(20 );
//
//    std::cout<<"TreeName NPR CCR MemoryConstraint AmountSubtrees AmountProcessors Makespan Heuristic TimeConsuming"<<std::endl;
//
//    ifstream OpenFile(dir+argv[2]);
//    do{
//        OpenFile>>treename;
//        parse_tree((dir+treename).c_str(), &tree_size, &prnts, &spacewghts, &ewghts,&timewghts);
//
//        num_processors=ceil(tree_size/NPR);
//        if(num_processors<3){
//            num_processors=3;
//        }
//        SetBandwidth(CCR, tree_size, ewghts, timewghts);
//
//        Ctree *treeobj = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
//        maxoutd = MaxOutDegree(treeobj, true);
//        po_construct(tree_size, prnts, &chstart,&chend,&children, &root);
//
//        time = clock();
//        makespan = treeobj->GetRoot()->GetMSCost();
//        number_subtrees = 1;
//        time = clock()-time;
//        cout<<treename<<" "<<NPR<<" "<<CCR<<" NA "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" Sequence "<<time<<endl;
//
//        schedule_t * schedule_f = new schedule_t();
//        count = 0;
//        MinMem(treeobj, maxoutd, minMem, *schedule_f, true, count);
//        delete schedule_f;
//        delete treeobj;
//
//        for (int stage2Method=0; stage2Method<3; ++stage2Method) {
//            for (int i=0; i<3; ++i){
//                Ctree *treeobj = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
//
//                memory_constraint = memory_constraint_options[i];
//                if (memory_constraint==1) {
//                    memorySize = maxoutd;
//                }else if (memory_constraint==2){
//                    memorySize = (maxoutd + minMem)/2;
//                }else{
//                    memorySize = minMem;
//                }
//
//                time=clock();
//                switch (stage2Method) {
//                    case 0:
//                        stage2heuristic = "FIRST_FIT";
//                        MemoryCheck(treeobj, chstart, children, memorySize, FIRST_FIT);
//                        break;
//                    case 1:
//                        stage2heuristic = "LARGEST_FIT";
//                        MemoryCheck(treeobj, chstart, children, memorySize, LARGEST_FIT);
//                        break;
//                    case 2:
//                        stage2heuristic = "IMMEDIATELY";
//                        MemoryCheck(treeobj, chstart, children, memorySize, IMMEDIATELY);
//                        break;
//
//                    default:
//                        stage2heuristic = "FIRST_FIT";
//                        MemoryCheck(treeobj, chstart, children, memorySize, IMMEDIATELY);
//                        break;
//                }
//                time=clock()-time;
//
//                makespan = treeobj->GetRoot()->GetMSCost(true,true);
//                number_subtrees = HowmanySubtrees(treeobj, true);
//
//                std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage2heuristic<<" "<<time<<endl;
//
//                if (number_subtrees > num_processors) {
//                    time = clock();
//                    makespan = MergeV2(treeobj, number_subtrees, num_processors, memorySize, chstart, children, true);
//                    time = clock() - time;
//                    number_subtrees = HowmanySubtrees(treeobj, true);
//                    std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage2heuristic<<"+Merge "<<time<<endl;
//                } else if (number_subtrees == num_processors){
//                    std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage2heuristic<<"+Nothing "<<0<<endl;
//                } else {
//                    time = clock();
//                    makespan = SplitAgain(treeobj, num_processors, number_subtrees);
//                    time = clock() - time;
//                    number_subtrees = HowmanySubtrees(treeobj, true);
//                    std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage2heuristic<<"+SplitAgain "<<time<<endl;
//                }
//
//                delete treeobj;
//            }
//        }
//
//        delete[] prnts;
//        delete[] ewghts;
//        delete[] spacewghts;
//        delete[] timewghts;
//        delete [] chstart;
//        delete [] chend;
//        delete [] children;
//    }while (OpenFile.good());
//    OpenFile.close();
//
//    return 0;
// }



//Created by changjiang GOU on 10/05/2018.
//Copyright © 2018 Changjiang GOU. All rights reserved.

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "lib-io-tree.h"
#include "heuristics.h"

int main(int argc, char** argv) {
    int c;
    string stage1, stage2="NA", stage3;
    bool broken_already=false;

    int memory_constraint;
    double CCR, NPR;

    string dir;
    string brokenEdgesFile_dir;
    bool quiet=false;

    while (1) {
        //int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[]={
            {"split",0,0,0},
            {"im",0,0,0},
            {"avoidchain",0,0,0},
            {"firstfit",0,0,0},
            {"immediately",0,0,0},
            {"largestfirst",0,0,0},
            {"ccr",1,0,0},
            {"npr",1,0,0},
            {"m",1,0,0},
            {"b",1,0,0},
            {"d",1,0,0},
            {0,0,0,0}
        };

        c = getopt_long(argc, argv, ":siafelqc:n:m:b:d:", long_options, &option_index);

        if (c==-1) {
            break;
        }

        switch (c) {
            case 's':
                stage1 = "SplitSubtrees";
                break;

            case 'i':
                stage1 = "ImprovedSplit";
                break;

            case 'a':
                stage1 = "AvoidChain";
                break;

            case 'f':
                stage2 = "FirstFit";
                break;

            case 'e':
                stage2 = "Immediately";
                break;

            case 'l':
                stage2 = "LargestFirst";
                break;

            case 'q':
                quiet = true;
                break;

            case 'c':
            {//double CCRs[] = {1, 0.1, 0.001};//communication to computation
                CCR=atof(optarg);
                break;
            }

            case 'n':
            {//double NPR[] = {1000, 100, 10};//amonut of nodes to processors
                NPR=atof(optarg);
                break;
            }

            case 'm':
            {
                memory_constraint = atoi(optarg);
            }
                break;

            case 'b':
            {
                broken_already=true;
                brokenEdgesFile_dir=optarg;
            }
                break;

            case 'd':
            {
                dir = optarg;
            }
                break;

            case '?':
                printf("Usage call-heuristics -s -i -a -f -e -l -c [ccr] -n [npr] -m [0|1|2] -b [brokenfile] Directory Treelist\n");

            default:
                break;
        }
    }

    if (optind >= argc) {
        printf("Please provide a tree.\n");
        exit(1);
    }

    int tree_size=0;
    int *prnts;
    double *ewghts, *spacewghts, *timewghts;
    list<Cnode*> parallelSubtrees;
    int *chstart,*chend,*children,root=1;
    string treename,buffer;
    char cur_char;
    unsigned int num_processors;
    double makespan,maxoutd,minMem,memorySize;
    uint64_t count;
    clock_t time;

    unsigned int number_subtrees;

    cout.precision(20);

    std::cout<<"TreeName "<<"NPR "<<"CCR "<<"MemoryConstraint "<<"AmountSubtrees "<<"AmountProcessors "<<"Makespan "<<"Stage1 "<<"Stage2 "<<"Stage3 "<<"TimeConsuming"<<std::endl;
    ifstream OpenFile(dir+argv[optind]);
    ifstream BrokenEdgesFile(brokenEdgesFile_dir);
    int memory_constraint_options[3]={1,2,3};
    std::vector<int> brokenEdges;
    do{
        OpenFile>>treename;
        parse_tree((dir+treename).c_str(), &tree_size, &prnts, &spacewghts, &ewghts,&timewghts);
        Ctree *treeobj = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);

        num_processors=ceil(tree_size/NPR);
        if (num_processors<3) {
            num_processors=3;
        }
        SetBandwidth(CCR, tree_size, ewghts, timewghts);

        if (broken_already) {
            time = 0;
            brokenEdges.clear();
            do{
                BrokenEdgesFile>>buffer;
                brokenEdges.push_back(stoi(buffer));
                treeobj->GetNode(stoi(buffer))->BreakEdge();//Edges already broken
                cur_char = BrokenEdgesFile.get();
            }while(cur_char != '\n' && BrokenEdgesFile.good());
            makespan=treeobj->GetRoot()->GetMSCost(true, true);
        }else{
            time = clock();
            if (stage1=="SplitSubtrees") {
                unsigned long sequentialLen;
                makespan = SplitSubtrees(treeobj->GetRoot(), num_processors, false, parallelSubtrees,sequentialLen);// for counting how many subtrees produced, twolevel is set as false
            }else if(stage1=="ImprovedSplit"){
                po_construct(tree_size, prnts, &chstart, &chend, &children, &root);
                makespan = ImprovedSplit(treeobj, num_processors, chstart, children);
                //makespan = ImprovedSplit(treeobj, num_processors);
            }else if(stage1=="AvoidChain"){
                makespan = ASAP(treeobj, num_processors);
                number_subtrees = HowmanySubtrees(treeobj,true);
                time = clock()-time;
                std::cout<<treename<<" "<<NPR<<" "<<CCR<<" NA "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<"ASAP NA NA "<<time<<std::endl;

                time = clock();
                number_subtrees = AvoidChain(treeobj);
                makespan=treeobj->GetRoot()->GetMSCost(true, true);
            }
            time = clock()-time;
        }
        number_subtrees = HowmanySubtrees(treeobj, quiet);
        std::cout<<treename<<" "<<NPR<<" "<<CCR<<" NA "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage1<<" NA NA "<<time<<std::endl;

        if (stage2 != "NA") {
            maxoutd = MaxOutDegree(treeobj, true);
            schedule_t * schedule_f = new schedule_t();
            count = 0;
            MinMem(treeobj, maxoutd, minMem, *schedule_f, true, count);
            delete schedule_f;
            po_construct(tree_size, prnts, &chstart, &chend, &children, &root);

            vector<Ctree*> trees;
            Ctree *treeobj2 = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
            Ctree *treeobj3 = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
            trees.push_back(treeobj3);
            trees.push_back(treeobj2);
            trees.push_back(treeobj);

            for (int i=0; i<3; ++i) {
                treeobj=trees.back();
                trees.pop_back();
                for (std::vector<int>::iterator it = brokenEdges.begin(); it!=brokenEdges.end(); ++it) {
                    treeobj->GetNode(*(it))->BreakEdge();//Edges already broken
                }

                memory_constraint = memory_constraint_options[i];
                if (memory_constraint==1) {
                    memorySize = maxoutd;
                }else if (memory_constraint==2){
                    memorySize = (maxoutd + minMem)/2;
                }else{
                    memorySize = minMem;
                }

                time=clock();
                if (stage2=="LargestFirst") {
                    MemoryCheck(treeobj, chstart, children, memorySize, LARGEST_FIT);
                }else if(stage2=="FirstFit"){
                    MemoryCheck(treeobj, chstart, children, memorySize, FIRST_FIT);
                }else if(stage2=="Immediately"){
                    MemoryCheck(treeobj, chstart, children, memorySize, IMMEDIATELY);
                }

                time=clock()-time;
                number_subtrees = HowmanySubtrees(treeobj, true);
                makespan = treeobj->GetRoot()->GetMSCost(true,true);
                std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage1<<" "<<stage2<<" NA "<<time<<std::endl;

                time=clock();
                if (number_subtrees>num_processors) {
                    stage3 = "Merge";
                    makespan = Merge(treeobj, number_subtrees, num_processors, memorySize, chstart, children, true);
                } else if (number_subtrees==num_processors) {
                    stage3 = "Nothing";
                } else {
                    stage3 = "SplitAgain";
                    makespan = SplitAgain(treeobj, num_processors, number_subtrees);
                }
                time=clock()-time;

                number_subtrees = HowmanySubtrees(treeobj, true);
                std::cout<<treename<<" "<<NPR<<" "<<CCR<<" "<<memory_constraint<<" "<<number_subtrees<<" "<<num_processors<<" "<<makespan<<" "<<stage1<<" "<<stage2<<" "<<stage3<<" "<<time<<std::endl;
                delete treeobj;
            }

            delete[] chstart;
            delete[] chend;
            delete[] children;
        }

        //delete treeobj;
        delete[] prnts;
        delete[] ewghts;
        delete[] spacewghts;
        delete[] timewghts;
    }while (OpenFile.good());
    OpenFile.close();
    BrokenEdgesFile.close();

    exit(EXIT_SUCCESS);
}


//-------------------------------------------------------------------------------



//  test
//  Created by changjiang GOU on 10/05/2018.
//  Copyright © 2018 Changjiang GOU. All rights reserved.

//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <math.h>
//#include <stdlib.h>
//#include "lib-io-tree.h"
//#include "heuristics.h"
//
//int main(int argc, const char * argv[]) {
//    int tree_size=0;
//    int *prnts;
//    double *ewghts, *spacewghts, *timewghts;
//
//    string treename, buffer;;
//
//    cout.precision(10);
//
//    double CCR = 1;
//
//    char cur_char;
//    string dir = "../../realTrees/";
//    //string brokenEdgesFile_dir = "../../result/brokenEdges/brokenEdges_is_9_v3.txt";
//    string brokenEdgesFile_dir = "../../result/brokenEdges/brokenEdges_split_9.txt";
//    ifstream OpenFile("../../realTrees/treesList.txt");
//    ifstream BrokenEdgesFile(brokenEdgesFile_dir);
//
//    do {
//        OpenFile>>treename;
//        parse_tree((dir+treename).c_str(), &tree_size, &prnts, &spacewghts, &ewghts,&timewghts);
//        Ctree *treeobj = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
//        SetBandwidth(1, tree_size, ewghts, timewghts);
//
//        do{
//            BrokenEdgesFile>>buffer;
//            treeobj->GetNode(stoi(buffer))->BreakEdge();//Edges already broken
//            cur_char = BrokenEdgesFile.get();
//        }while(cur_char != '\n' && BrokenEdgesFile.good());
//
//        Ctree* Qtree = BuildQtree(treeobj);
//        Cnode* currentSubtree = Qtree->GetRoot();
//
//        cout<<"------------------------------------------------------------------------------------"<<endl;
//        cout<<"tree name: "<<treename<<", tree size: "<<treeobj->GetNodes()->size()<<", Qtree size: "<<Qtree->GetNodes()->size()<<", MS "<<currentSubtree->GetMSCost(true,true)<<endl;
//        unsigned int number_subtrees = HowmanySubtrees(treeobj, false);
//
//        list<Cnode*> tempQue;
//        vector<Cnode*>* Qchildren;
//        tempQue.push_back(currentSubtree);
//        while (!tempQue.empty()) {
//            currentSubtree = tempQue.front();
//            tempQue.pop_front();
//            cout<<"node "<<currentSubtree->GetId()<<", size "<<currentSubtree->GetMSW()<<", communication cost "<<currentSubtree->GetEW()/BANDWIDTH<<endl;
//            cout<<"   children{ ";
//            Qchildren = currentSubtree->GetChildren();
//            for (vector<Cnode*>::iterator iter=Qchildren->begin(); iter!=Qchildren->end(); ++iter) {
//                cout<<(*iter)->GetId()<<" ";
//                tempQue.push_back((*iter));
//            }
//            cout<<"}"<<endl;
//        }
//        cout<<"------------------------------------------------------------------------------------"<<endl;
//
//        delete treeobj;
//        delete[] prnts;
//        delete[] ewghts;
//        delete[] spacewghts;
//        delete[] timewghts;
//    } while (OpenFile.good());
//
//    return 0;
//}



//#include <iostream>
//#include <fstream>
//#include <string>
//#include <math.h>
//#include <stdlib.h>
//#include "lib-io-tree.h"
//#include "heuristics.h"
//
//void PrintTree(Ctree* tree){
//    const vector<Cnode*>* children = tree->GetNodes();
//    cout<<"nodeId   parentId   ms_weight   me_weight   edge_weight"<<endl;
//    for (vector<Cnode*>::const_iterator it=children->begin(); it!=children->end(); ++it) {
//        cout<<(*it)->GetId()<<" "<<(*it)->GetParentId()<<" "<<(*it)->GetMSW()<<" "<<(*it)->GetNW()<<" "<<(*it)->GetEW()<<endl;
//    }
//    cout<<endl;
//}
//
//
//int main(int argc, const char * argv[]) {
//    int tree_size=0;
//    int *prnts;
//    double *ewghts, *spacewghts, *timewghts;
//    int *chstart,*chend,*children,root=1;
//    string treename, buffer;;
//
//    cout.precision(10);
//
//    string tree = "../../test/example10.tree.nf";
//
//    parse_tree(tree.c_str(), &tree_size, &prnts, &spacewghts, &ewghts,&timewghts);
//    Ctree *treeobj = new Ctree(tree_size,prnts,spacewghts,ewghts,timewghts);
//    
//    PrintTree(treeobj);
//
//    double NPR = 100;
//    double CCR = 1;
//    SetBandwidth(CCR, tree_size, ewghts, timewghts);
//
//    unsigned int numberProcessors=ceil(tree_size/NPR);
//    if (numberProcessors<3) {
//        numberProcessors=3;
//    }
//
////    po_construct(tree_size, prnts, &chstart, &chend, &children, &root);
////    double makespan = ImprovedSplit(treeobj, numberProcessors, chstart, children);
////    cout<<"makespan of ImprovedSplit: "<<makespan<<endl;
//
//    double makespan = treeobj->GetRoot()->GetMSCost();
//    cout<<"makespan before "<<makespan<<endl;
//    
//    double maxoutd = MaxOutDegree(treeobj, true);
//    po_construct(tree_size, prnts, &chstart, &chend, &children, &root);
//    MemoryCheck(treeobj, chstart, children, maxoutd, LARGEST_FIT);
//    makespan = treeobj->GetRoot()->GetMSCost(true,true);
//    cout<<"makespan now "<<makespan;
//    
//    delete[] chstart;
//    delete[] chend;
//    delete[] children;
//    delete treeobj;
//    delete[] prnts;
//    delete[] ewghts;
//    delete[] spacewghts;
//    delete[] timewghts;
//    return 0;
//}


// #include <iostream>
// #include <fstream>
// #include <string>
// #include <math.h>
// #include <stdlib.h>
// #include "lib-io-tree.h"
// #include "heuristics.h"
//
// int main(int argc, const char * argv[]) {
//    int tree_size=0;
//    int *prnts;
//    double *ewghts, *spacewghts, *timewghts;
//    string dir=argv[1];
//    string treename;
//
//    double NPR[] = {10000, 1000, 100};//ratio of nodes' amount to processors
//
//    unsigned int num_processors;
//
//    cout.precision(20 );
//    std::cout<<"TreeName NPR CCR MemoryConstraint AmountSubtrees AmountProcessors Makespan Heurisitc TimeConsuming"<<std::endl;
//
//    ifstream OpenFile(dir+argv[2]);
//    cout<<"name size npr_10000 npr_1000 npr_100"<<endl;
//    do{
//        OpenFile>>treename;
//        parse_tree((dir+treename).c_str(), &tree_size, &prnts, &spacewghts, &ewghts,&timewghts);
//
//        cout<<treename<<" "<<tree_size<<" ";
//        for (unsigned int i=0; i<3; i++) {
//            num_processors=ceil(tree_size/NPR[i]);
//            cout<<num_processors<<" ";
//        }
//        cout<<endl;
//
//        delete[] prnts;
//        delete[] ewghts;
//        delete[] spacewghts;
//        delete[] timewghts;
//    }while (OpenFile.good());
//    OpenFile.close();
//
//    return 0;
// }


// #include <iostream>
// #include <stdio.h>
// #include <time.h>
//
// int main(int argc, const char * argv[]) {
//
//     std::cout<<"clock ticks per second: "<<(unsigned long)CLOCKS_PER_SEC<<std::endl;
//
//    return 0;
// }
