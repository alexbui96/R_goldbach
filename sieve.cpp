#include "sieve.h"

static bool IntegerDivisible(int,int);

static bool IntegerDivisible(
        int Numer,
        int Denom)
{
        if (Numer%Denom == 0 &&
            Numer/Denom > 1) return true;
        else return false;
}       /* end IntegerDivisible */

int main()
{
        int i,N,option;
        char answer[10];
        GOLDBACH gb;

repeat_run:
        printf("Enter upper bound of the number: ");
        scanf("%d",&N);

diff_method:
        printf("Available options are:\n");
        printf("\tCompute G-pairs inwards (1)\n");
        printf("\tCompute G-pairs outwards (2)\n");
        printf("\tCompute ratio (3)\n");
        printf("\tCompute Meissel–Mertens constant (4)\n");
        printf("Enter option: ");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            gb.GoldbachInward(N);
            break;
        case 2:
            gb.GoldbachOutward(N);
            break;
        case 3:
            gb.ComputePrimeGap(N);
            break;
        case 4:
            gb.ComputeMeisselMertens(N);
            break;
        default:
            exit(0);
        }
        /*
        printf("Test different analysis with same bound? ");
        scanf("%s",answer);
        if (answer[0] == 'y') goto diff_method;
        */
        printf("\nCurrent upper bound is %d, test a different bound? ",gb.Nmax);
        scanf("%s",answer);
        if (answer[0] == 'y') goto repeat_run;
}

void GOLDBACH::ComputePrimeGap(
        int N)
{
        double ratio = 0.0;
        int i,j;

        if (Nmax != N)
        {
            InitPrimes(N);
            Nmax = N;
        }

        for (i = 0; i < primes.size(); ++i)
            ratio += 1.0/primes[i];
        for (i = 0; i < primes.size()-1; ++i)
            for (j = i+1; j < primes.size(); ++j)
                ratio -= 1.0/primes[i]/primes[j];
        printf("ratio = %f\n",ratio);
}       /* end ComputePrimeGap */

void GOLDBACH::GoldbachOutwardSave(
        int N)
{
        int i,EN;
        int max_search = 0;
        int num_twins = 0;
        int ave_search = 0;
        GPAIR gpair;

        for (i = 4; i < N/4; ++i)
        {
            EN = 2*i;
            if (FindNearestPrimePair(EN,gpair))
            {
                gpairs.push_back(gpair);
            }
            else
            {
                printf("Counter example found for: %d\n",EN);
            }
        }
        for (i = 0; i < gpairs.size(); ++i)
        {
            printf("E: %d primes: (%d,%d) N-search: %d\n",
                    gpairs[i].Ne,gpairs[i].p1,gpairs[i].p2,
                    gpairs[i].num_search);
            if (gpairs[i].num_search > max_search)
                max_search = gpairs[i].num_search;
            if (gpairs[i].p2 - gpairs[i].p1 == 2)
                num_twins++;
        }
        printf("Last staked prime number p(%d): %d\n",
                (int)stacked_primes.size(),stacked_primes.back());
        printf("Last sieved prime number p(%d): %d\n",
                (int)primes.size(),primes.back());
        printf("Max number of search: %d\n",max_search);
        printf("Number of twins: %d\n",num_twins);
}       /* end GoldbachOutwardSave */

void GOLDBACH::GoldbachOutward(
        int N)
{
        int i,EN;
        int max_search = 0;
        int num_twins = 0;
        int ave_search = 0;
        int il,ir,ns,imax;
        int sum;
        GPAIR gpair;
        vector<int> twins;
        char answer[10];

        if (Nmax != N)
        {
            InitPrimes(N);
            Nmax = N;
        }

        for (i = 4; i < N/4; ++i)
        {
            EN = 2*i;

            il = FindLeftPrimeIndex(i);
            ir = il + 1;
            ns = 0;
            if (2*primes[il] == EN)
            {
                gpair.p1 = primes[il];
                gpair.p2 = primes[il];
                gpair.Ne = EN;
                gpair.num_search = ns;
                gpairs.push_back(gpair);
                continue;
            }
            while (true)
            {
                ns++;
                sum = primes[il] + primes[ir];
                if (sum == EN)
                {
                    gpair.p1 = primes[il];
                    gpair.p2 = primes[ir];
                    gpair.Ne = EN;
                    gpair.num_search = ns;
                    gpairs.push_back(gpair);
                    break;
                }
                else if (sum < EN) ir++;
                else il--;
                if (il <= 0 || ir >= primes.size())
                {
                    printf("EN = %d  il = %d  ir = %d\n",EN,il,ir);
                    printf("Counter example found, check details!\n");
                    exit(0);
                }
            }
        }
        for (i = 0; i < gpairs.size(); ++i)
        {
            if (gpairs[i].num_search > max_search)
            {
                max_search = gpairs[i].num_search;
                imax = i;
            }
            if (gpairs[i].p2 - gpairs[i].p1 == 2)
            {
                num_twins++;
                twins.push_back(i);
            }
        }
        printf("Last staked prime number p(%d): %d\n",
                (int)stacked_primes.size(),stacked_primes.back());
        printf("Last sieved prime number p(%d): %d\n",
                (int)primes.size(),primes.back());
        printf("Max number of search: %d\n",max_search);
        printf("Case with max number of search: EN: %d primes: (%d, %d)\n",
                gpairs[imax].Ne,gpairs[imax].p1,gpairs[imax].p2);
        printf("Print Goldbach pairs? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
        {
            for (i = 0; i < gpairs.size(); ++i)
                printf("E: %d primes: (%d,%d) N-search: %d\n",
                        gpairs[i].Ne,gpairs[i].p1,gpairs[i].p2,
                        gpairs[i].num_search);
        }
        printf("Number of twins: %d\n",num_twins);
        printf("Print twins? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
        {
            for (i = 0; i < twins.size(); ++i)
                printf("twin: (%d, %d)\n",
                        gpairs[twins[i]].p1,gpairs[twins[i]].p2);
        }
}       /* end GoldbachOutward */

void GOLDBACH::GoldbachInward(
        int N)
{
        int i,j,EN;
        int num_twins = 0;
        int ave_search = 0;
        int imax;
        GPAIR gpair;
        char answer[10];

        if (Nmax != N)
        {
            InitPrimes(N);
            Nmax = N;
        }

        gpairs.resize(0);
        for (i = 4; i < N/4; ++i)
        {
            EN = 2*i;
            for (j = 1; j < primes.size(); ++j)
            {
                if (IsInPrimeList(EN-primes[j]))
                {
                    gpair.Ne = EN;
                    gpair.p1 = primes[j];
                    gpair.p2 = EN - primes[j];
                    gpair.num_search = j;
                    gpairs.push_back(gpair);
                    break;
                }
            }
        }
        max_search = 0;
        for (i = 0; i < gpairs.size(); ++i)
        {
            if (gpairs[i].num_search > max_search)
            {
                max_search = gpairs[i].num_search;
                imax = i;
            }
        }
        printf("Print Goldbach pairs? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
        {
            for (i = 0; i < gpairs.size(); ++i)
                printf("E: %d primes: (%d,%d) N-search: %d\n",
                        gpairs[i].Ne,gpairs[i].p1,gpairs[i].p2,
                        gpairs[i].num_search);
        }
        printf("Last staked prime number p(%d): %d\n",
                (int)stacked_primes.size(),stacked_primes.back());
        printf("Last sieved prime number p(%d): %d\n",
                (int)primes.size(),primes.back());
        printf("Max number of search: %d\n",max_search);
        printf("Analyze Goldbach pair cases? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
            GoldbachInwardAnalysis();
}       /* end GoldbachInward */

bool GOLDBACH::FindNearestPrimePair(
        int EN,
        GPAIR& gpair)
{
        int i;
        for (i = 0; i < EN/2-1; ++i)
        {
            if (IsInPrimeList(EN/2+i) &&
                IsInPrimeList(EN/2-i))
            {
                gpair.Ne = EN;
                gpair.p1 = EN/2-i;
                gpair.p2 = EN/2+i;
                gpair.num_search = i + 1;
                return true;;
            }
        }
        return false;
}       /* end FindNearestPrimePair */

bool GOLDBACH::IsInPrimeList(
        int N)
{
        int n,nl,nu;
        nl = 0;    
        nu = primes.size() - 1;
        if (primes[nl] == N) return true;
        else if (primes[nu] == N) return true;
        while (true)
        {
            n = (nl + nu)/2;
            if (primes[n] == N) return true;
            else if (primes[n] > N) nu = n;
            else nl = n;
            if (nu-nl <= 1) 
            {
                if (primes[nl] == N) return true;
                else if (primes[nu] == N) return true;
                else return false;
            }
        }
}       /* end IsInPrimeList */

void GOLDBACH::InitPrimes(
        int N)
{
        int i,l,m,p;
        int num_primes,num_hits,N_max_hits;
        int p_max,hit_max;
        vector<int> sieve;
        char answer[10];

        sieve.resize(N);
        primes.resize(0);
        stacked_primes.resize(0);
        gpairs.resize(0);

        for (m = 0; m < N; ++m)
            sieve[m] = 0;
        sieve[0] = sieve[1] = 1;

        m = p = 2;
        p_max = floor(sqrt(N));
        stacked_primes.push_back(p);
        i = 2;
        while (m < N)
        {
            m = i*p;
            if (m >= N)
            {
                for (p = p+1; p <= p_max; ++p)
                {
                    if (sieve[p] == 0) 
                    {
                        stacked_primes.push_back(p);
                        break;
                    }
                }
                i = 2;
                m = i*p;
                if (m >= N) break;
            }
            sieve[m]++; 
            i++;
        }

        num_primes = num_hits = 0;
        hit_max = 0;
        for (m = 0; m < N; ++m)
        {
            if (sieve[m] == 0)
            {
                primes.push_back(m);
                num_primes++;
            }
            else
            {
                num_hits += sieve[m];
                if (hit_max < sieve[m])
                {
                    hit_max = sieve[m];
                    N_max_hits = m;
                }
            }
        }
        printf("Number of stacked primes: %d\n",(int)stacked_primes.size());
        printf("Back of stacked primes: %d\n",stacked_primes.back());
        printf("Number of all primes: %d\n",num_primes);
        printf("Back of primes: %d\n",primes.back());
        /*
        printf("Total number of hits: %d\n",num_hits);
        printf("Max hits: %d\n",hit_max);
        printf("Number with max hits: %d\n",N_max_hits);
        */
        printf("Print all stacked primes? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
        {
            for (i = 0; i < stacked_primes.size(); ++i)
                printf("stacked primes: %d\n",stacked_primes[i]);
        }
        printf("Print all primes? ");
        scanf("%s",answer);
        if (answer[0] == 'y')
        {
            for (i = 0; i < primes.size(); ++i)
                printf("Primes: %d\n",primes[i]);
        }
}       /* InitPrimes */

int GOLDBACH::FindLeftPrimeIndex(
        int N)
{
        int il,ir,im;
        il = 0;
        ir = primes.size() - 1;
        if (N > primes[ir] || N < 3) return -1;
        while (true)
        {
            if (primes[il] == N) return il;
            else if (primes[ir] == N) return ir;
            else if (ir - il == 1) return il;

            im = (il + ir)/2;

            if (primes[im] >= N)
                ir = im;
            else
                il = im;
        }
}       /* end FindLeftPrimeIndex */

void GOLDBACH::GoldbachInwardAnalysis()
{
        int i,ns,m;
        vector<int> nscase;     // Cases with number of searches
        char answer[10];

        nscase.resize(max_search+1);
        for (i = 0; i < gpairs.size(); ++i)
        {
            nscase[gpairs[i].num_search]++;
        }

new_search_number:
        for (i = 0; i < nscase.size(); ++i)
            printf("Number of search: %d  number of cases: %d\n",i,nscase[i]);
        printf("Choose case with number of searches: ");
        scanf("%d",&ns);
        printf("There are %d cases with %d searches\n\n",nscase[ns],ns);
        m = 0;
        for (i = gpairs.size()-1; i >= 0; --i)
        {
            if (gpairs[i].num_search == ns)
            {
                printf("Case %d: EN = %d  pl = %d  pr = %d\n",m,
                        gpairs[i].Ne,gpairs[i].p1,gpairs[i].p2);
                FullInwardAnalysis(i);
                printf(COLOR_RESET"\n\nType n for next case, b to break: ");
                scanf("%s",answer);
                if (answer[0] == 'n') continue;
                else break;
                m++;
            }
        }
        printf("Choose case with different number of searches? ");
        scanf("%s",answer);
        if (answer[0] == 'y') goto new_search_number;
}       /* end GoldbachInwardAnalysis */

void GOLDBACH::GoldbachOutwardAnalysis()
{
}       /* end GoldbachInwardAnalysis */

void GOLDBACH::FullInwardAnalysis(
        int n)
{
        int i,j,k,nd;
        char answer[10];

        for (j = 1; j < primes.size(); ++j)
        {
            int ER = gpairs[n].Ne - primes[j];
            if (j >= stacked_primes.size())
                printf(COLOR_YELLOW);
            else
                printf(COLOR_GREEN);
            printf("ER = %d-%d=%d is divisible by: ",gpairs[n].Ne,
                    primes[j],ER);
            nd = 0;
            for (k = 0; k < stacked_primes.size(); ++k)
            {
                if (IntegerDivisible(ER,stacked_primes[k]))
                {
                    printf("%d ",stacked_primes[k]);
                    nd++;
                }
            }
            if (nd == 0) break;
            printf(COLOR_RESET"\n");
        }

        int option;
        int base = 3;
        int ncl,npl;            // Left number of Composites and primes 
        int ncr,npr;            // Right number of Composites and primes
        int ncs,nps;            // Symmetric number of Composites and primes
        int lnf,rnf;            // Left and right factors.
        int npairs;
        bool lp,rp;

repeat_analysis:
        printf(COLOR_RESET"\n\nAnalysis of all odd pairs\n");
        printf("Print options are\n");
        printf("\tPrint all (0)\n");
        printf("\tPrint symmetric primes (1)\n");
        printf("\tPrint symmetric composites (2)\n");
        printf("\tPrint all left primes (3)\n");
        printf("\tPrint all left composites (4)\n");
        printf("\tPrint all right primes (5)\n");
        printf("\tPrint all right composites (6)\n");
        printf("\tPrint left-only composites (7)\n");
        printf("\tPrint right-only composites (8)\n");
        printf("Enter print option: ");
        scanf("%d",&option);

        j = 0;
        ncl = npl = ncr = npr = nps = ncs = 0;
        lnf = rnf = 0;
        npairs = 0;
        while (base+2*j <= stacked_primes.back())
        {
            int ER = gpairs[n].Ne - base - 2*j;

            int lf,rf;
            lf = rf = 0;
            for (k = 0; k < stacked_primes.size(); ++k)
                if (IntegerDivisible(base+2*j,stacked_primes[k]))
                    lf++;
            for (k = 0; k < stacked_primes.size(); ++k)
                if (IntegerDivisible(ER,stacked_primes[k]))
                    rf++;

            /* Filtering options */
            if ((lf != 0 || rf != 0) && option == 1)
            {
                j++;
                continue;
            }
            if ((lf == 0 || rf == 0) && option == 2)
            {
                j++;
                continue;
            }
            if (lf != 0 && option == 3)
            {
                j++;
                continue;
            }
            if (lf == 0 && option == 4)
            {
                j++;
                continue;
            }
            if (rf != 0 && option == 5)
            {
                j++;
                continue;
            }
            if (rf == 0 && option == 6)
            {
                j++;
                continue;
            }
            if ((lf == 0 || rf != 0) && option == 7)
            {
                j++;
                continue;
            }
            if ((lf != 0 || rf == 0) && option == 8)
            {
                j++;
                continue;
            }

            printf(COLOR_RESET"ER = %d-%d=%d\n",gpairs[n].Ne,base+2*j,ER);
            if (base+2*j > stacked_primes.back())
                printf(COLOR_YELLOW);
            else
                printf(COLOR_GREEN);
            printf(" Left %7d is divisible by: ",base+2*j);
            for (k = 0; k < stacked_primes.size(); ++k)
            {
                if (IntegerDivisible(base+2*j,stacked_primes[k]))
                {
                    printf("%d ",stacked_primes[k]);
                    lnf++;
                }
            }
            printf("\n");
            printf("Right %7d is divisible by: ",ER);
            for (k = 0; k < stacked_primes.size(); ++k)
            {
                if (IntegerDivisible(ER,stacked_primes[k]))
                {
                    printf("%d ",stacked_primes[k]);
                    rnf++;
                }
            }
            printf(COLOR_RESET"\n");
            lp = IsInPrimeList(base+2*j);
            rp = IsInPrimeList(ER);
            if (lp) npl++;
            else ncl++;
            if (rp) npr++;
            else ncr++;
            if (lp && rp) 
            {
                printf(COLOR_YELLOW"\tSymmetric prime pair: %d %d\n",
                            base+2*j,ER);
                nps++;
            }
            if (!lp && !rp) 
            {
                printf(COLOR_RED"\tSymmetric composite pair: %d %d\n",
                            base+2*j,ER);
                ncs++;
            }
            npairs++;
            j++;
        }
        printf(COLOR_RESET"\nNumber of cases: %d\n",npairs);
        if (option == 0)
        {
            printf("\n Ceiling of stacked primes: %d\n",stacked_primes.back());
            printf("  Number of stacked primes: %d\n",stacked_primes.size());
            printf("  Number of odd composites: %d\n",
                    (stacked_primes.back()-1)/2-stacked_primes.size()+1);
            printf(COLOR_RESET"Total number of odd pairs: %d\n",
                    (stacked_primes.back()-base)/2+1);
            printf(" Number of left primes and composites: %d %d\n",npl,ncl);
            printf("Number of right primes and composites: %d %d\n",npr,ncr);
            printf("Number of symmetric composites: %d\n",ncs);
            printf("Difference of right and symmetric composites: %d\n",ncr-ncs);
            printf("Number of symmetric primes: %d\n",nps);
            printf("Left and right factors: %d  %d ratio: %5.3f\n",lnf,rnf,
                    (double)rnf/(double)lnf);
            printf("\n");
        }
        printf(COLOR_RESET"\nAnother option? ");
        scanf("%s",answer);
        if (answer[0] == 'y') goto repeat_analysis;

}       /* end FullInwardAnalysis */

void GOLDBACH::ComputeMeisselMertens(
        int N)
{
        int i;
        double sum,llog;

        if (Nmax != N)
        {
            InitPrimes(N);
            Nmax = N;
        }
        llog = log(log(primes.back()));
        sum = 0;
        for (i = 0; i < primes.size(); ++i)
        {
            sum += 1.0/primes[i];
        }
        printf("Sum = %f  Loglog = %f\n",sum,llog);
        printf("Sum-Loglog = %16.14f  MM = %16.14f\n",sum-llog,MM);
        printf("Error: %16.14f  Relative error = %16.14f\n",
                        sum-llog-MM,(sum-llog-MM)/MM);
}       /* end ComputeMeisselMertens */