/*
 * Project on String Matching Algorithms Analysis
 * Course: Analysis and Design of Algorithms CSCI-B 503
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <sstream>
#include <ctime>
#include <array>
#include <cstring>
using namespace std;

vector <vector <string> > data;

void read_file(string filename){
  ifstream inputDS;
  inputDS.open(filename);
  
  if(inputDS.is_open()){
	  while(!inputDS.eof()){
		  vector <string> row;
		  string temp_row;
		  
		  if (!getline(inputDS, temp_row))
			break;
			
		  istringstream temp_stm(temp_row);
		  
		  while (temp_stm){
			string temp_str;
			
			if (!getline(temp_stm, temp_str, '\t'))
				break;
				
			row.push_back(temp_str);
		  }
		  
		  data.push_back(row);
	  }
	  inputDS.close();
  }
  else{
	  cout<<"Error opening file:"<<filename;
  }
  
  //int v = 0;
  //for(auto const& inner_word : data){
		//int u = 0;
		//for(auto const& s : inner_word){
			//cout << s<<'\t';
			//if(u%2==1)
				//cout<<'\n';
			//u++;
		//}
		//if(v%2==0)
			//cout<<endl;
		//v++;
  //}
        
  //cout <<"end";
}

int naive(string main_str, string sub_str){
    int retval = 0;
    //int pos = -1;
    int i_mlen = main_str.size();
    int i_slen = sub_str.size();
    for(int i=0;i<i_mlen;){
		for(int j=0;j<i_slen;){
			retval++;
			if(main_str[i]!=sub_str[j]){
				i++;j++;
				break;
			}
			else{
				i++;j++;
				if(j==i_slen){					
					//pos = i - j;
					break;
				}
			}
		}
	}
	//return pos;
	return retval;
}

int rabin(string main_str, string sub_str){
	int retval = 0;
	
	int i_hval = 101, d = 256;
	int i_mlen = main_str.size(), i_slen = sub_str.size();
    int p = 0, t = 0, h = 1, i, j;
     
    int r1=0, r2=0;
    for(i = 0; i < i_slen-1; i++){
        h = (h*d) % i_hval;
        r1++;
	}
 
    for(i = 0; i < i_slen; i++){
        p = (d*p + sub_str[i]) % i_hval;
        t = (d*t + main_str[i]) % i_hval;
        r2++;
    }
    
    //int found = -1;
    for(i = 0; i <= i_mlen - i_slen; i++){
        if( p == t ){
            for(j = 0; j < i_slen; j++){
                if(main_str[i+j] != sub_str[j])
                    break;
            }
            if(j == i_slen){
                //found = i;
                break;
			}
        }
 
        if( i < i_mlen - i_slen ){
            t = (d*(t - main_str[i]*h) + main_str[i + i_slen]) % i_hval;
            if(t < 0)
				t = (t + i_hval);
        }
    retval++;
    }
    //return found;
    return max(retval,max(r1,r2));
}

int knuth_util(string sub_str, int f[]){
    int retval = 0;
    int m = sub_str.size(), k;
    f[0] = -1;
    for (int i = 1; i < m; i++){
        k = f[i - 1];
        while (k >= 0){
            if (sub_str[k] == sub_str[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
        retval++;
    }
    return retval;
}

int knuth(string main_str, string sub_str){
    int retval = 0;
    
    int m = sub_str.size();
    int n = main_str.size();
    int f[m];     
    int ku = knuth_util(sub_str, f);
    int i = 0, k = 0;
    //int found = -1;
    
    while(i < n){
        if (k == -1){
            i++;
            k = 0;
        }
        else if (main_str[i] == sub_str[k]){
            i++;
            k++;
            if (k == m){
                //found = k;
                break;
			}
        }
        else
            k = f[k];
	retval++;
    }
    //return n-found-1;
    return retval+ku;
}

int boyre_util(string sub_str, int size, int badchar[256]){
    int i, j;    
    for (i = 0; i < 256; i++)
        badchar[i] = -1;
 
    for (j = 0; j < size; j++)
        badchar[(int) sub_str[j]] = j;
        
    return max(i,j);
}
 
int boyre(string main_str, string sub_str){
    int retval = 0;
    
    int m = sub_str.size();
    int n = main_str.size(); 
    int d = 256;
    int badchar[d]; 
    //int found = -1;
    int bu = boyre_util(sub_str, m, badchar);
    int s = 0;
    while (s <= (n - m)){
        int j = m - 1; 
        while (j >= 0 && sub_str[j] == main_str[s + j])
            j--;
 
        if (j < 0){
            //found = s;
            s += (s + m < n) ? m - badchar[(int)main_str[s + m]] : 1; 
        }
        else
            s += max(1, j - badchar[(int)main_str[s + j]]);
    retval++;
    }
    //return found;
    return retval+bu;
}

long int get_a_sum(int arr[], int size){
	long int sum = 0;
	for(int i=0;i<size;i++){
		sum += arr[i];
	}
	return sum;
}

double get_a_avg(int arr[]){
	//int size = sizeof(arr)/sizeof(arr[0]);
	int size = 3106;
	long int sum = get_a_sum(arr,size);		
	double avg = double(sum)/size;
	return avg;
}

void write_file(int arr1[], int arr2[], int arr3[], int arr4[], int count, double avg_main_str_len){

	stringstream ss;
	ss << "output_"<<avg_main_str_len<<".txt";
	string fname = ss.str();
	
	ofstream fout(fname);
	if(fout.is_open())
	{
		//for(int i = 0; arr[i] != '\0'; i++){
		//int siz = sizeof(arr)/sizeof(int);
		//fout << "Sl. No.\tNaive\tRabin Karp\tKnuth Moris\tBoyreMore"<<endl<<"Average text length:"<<avg_main_str_len<<endl;
		
		//fout << "Sl. No.\tNaive\tRabin Karp\tKnuth Moris\tBoyreMore"<<endl;
		
		/*for(int i=0;i< count;i++){
			fout <<i<<'\t'<<arr1[i]<<'\t'<<arr2[i]<<'\t'<<arr3[i]<<'\t'<<arr4[i]<<endl;
		}*/	
		
		fout<<get_a_avg(arr1)<<"\t"<<get_a_avg(arr2)<<"\t"<<get_a_avg(arr3)<<"\t"<<get_a_avg(arr4)<<endl;
		
		//fout<<endl<<"EOF";
		fout.close();
    }
}

int main(int argc, char *argv[])
{
	/*command line argument
	if(argc==1){
		cout<<"Usage:"<<argv[0]<<"<text> <pattern>"<<endl;
	}
	else{
		readFile();
		string s1(argv[1]);
		if(argc==2 && s1.compare("--help")==0){
			cout<<"Usage:"<<argv[0]<<"<text> <pattern>"<<endl;
		}
		else{
			string s2(argv[2]);			
			//cout<<endl<<"Naive position:"<<naive(s1, s2)<<endl<<endl;
		}
	}
	cout <<"end";*/
	
	
	if(argc>1){       
		for(int i_count = 1; i_count<argc;i_count++){
			string filename(argv[i_count]);
			read_file(filename);
			int ia_naive[3106];
			int ia_rabin[3106];
			int ia_knuth[3106];
			int ia_boyre[3106];
	
			int cnt = 0;
			long int sum_sizes = 0;
			for(auto const& inner_word : data){
				ia_naive[cnt] = naive(inner_word[0], inner_word[1]);
				ia_rabin[cnt] = rabin(inner_word[0], inner_word[1]);
				ia_knuth[cnt] = knuth(inner_word[0], inner_word[1]);
				ia_boyre[cnt] = boyre(inner_word[0], inner_word[1]);
				sum_sizes+= inner_word[0].size();
				cnt++;
			}
			double avg_main_str_len = (double)sum_sizes/cnt;	
	
			write_file(ia_naive, ia_rabin, ia_knuth, ia_boyre, cnt, avg_main_str_len);
		}
	}
	else{
		string s1(argv[1]);
		read_file(s1);
	}
	return 0;
}
