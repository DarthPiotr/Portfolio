ofstream file("bts-search-2.txt", ofstream::out);
    const int N = 2000000;
    //const int X = 3000;
    //int arr[X];
    int time = 0;
    int add = 5000;
    for(int n=5000; n<=N; n+=add)
    {
        struct BST *test  = new BST();
        test->add(1);
        time = 0;

        for(int i=0; i<n; i++)
        {
            int x = rand()%100000000;
            test->add(x);
            //if(i<X)
            //    arr[i] = x;

        }
        cout<<"#";
        for(int k=0; k<2; k++)
        {

            std::chrono::time_point<std::chrono::high_resolution_clock> time_start = std::chrono::high_resolution_clock::now();
            for(int j=0; j<10000; j++)
            {
                //test.find(j);
                test->findMaximum();
                test->findMinimum();
                for(int q=0;q<100;q++)
                test->find(rand()%100000000);
                //cout<<"@";
                //test->remove(j);
                //cout<<"!";
            }
            std::chrono::time_point<std::chrono::high_resolution_clock>  time_finish = std::chrono::high_resolution_clock::now();
            time += std::chrono::duration_cast<std::chrono::milliseconds>(time_finish - time_start).count();

        }
        time /= 2;
        cout<<time<<" "<<n<<endl;
        file<<time<<" "<<n<<endl;
        delete test;
        if(n%25000 == 0)
            add+= 5000;
    }