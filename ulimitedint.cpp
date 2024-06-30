/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

//  int size;
//  int sign; // 1 if positive, -1 if negative
//  int capacity; // Capacity of the unlimited_int array
//  int* unlimited_int; // The array to store the unlimited int

UnlimitedInt::UnlimitedInt(){
    size = 1;
    capacity = 1;
    sign = 0;
    int* a = new int[1];
    a[0] = 0;
    unlimited_int = a;
}


UnlimitedInt::UnlimitedInt(string s){
    if(s[0]!='-'){

        int id = 0;
        while (s[id] == '0'){
            id++;
        }
        s.erase(0,id);
    }

    else if (s[0] == '-'){
        int id = 1;
        while (s[id] == '0'){
            id++;
        }
        s.erase(1,id-1);
    }

    if (s == "" || s== "-"){
        size = 1;
        capacity = 1;
        sign = 0;
        int* a = new int[1];
        a[0] = 0;
        unlimited_int = a;
    }
    

    else if (s[0]=='-'){
        int n = s.length();
        sign = -1;
        n = n-1;
        size = n;
        capacity = n;
        int* a = new int[n];
        for (int i=1;i<s.length();i++){
            a[i-1] = int(s[i]) - int('0');
        }
        unlimited_int = a;
    }

    else{
        int n = s.length();
        sign = 1;
        size = n;
        capacity = n;
        int* a = new int[n];
        for (int i=0;i<s.length();i++){
            a[i] = int(s[i]) - int('0');
        }
        unlimited_int = a;
    }
}


UnlimitedInt::UnlimitedInt(int i){
    string s = "";
    if (i>=0){
        s = std::to_string(i);
    }
    else{
        int k = -1*i;
        s = std::to_string(k);
        s = '-' + s;
    }
    if(s[0]!='-'){
        int id = 0;
        while (s[id] == '0'){
            id++;
        }
        s.erase(0,id);
    }

    else if (s[0] == '-'){
        int id = 1;
        while (s[id] == '0'){
            id++;
        }
        s.erase(1,id-1);
    }

    if (s == "" || s== "-"){
        size = 1;
        capacity = 1;
        sign = 0;
        int* a = new int[1];
        a[0] = 0;
        unlimited_int = a;
    }
    

    else if (s[0]=='-'){
        int n = s.length();
        sign = -1;
        n = n-1;
        size = n;
        capacity = n;
        int* a = new int[n];
        for (int i=1;i<s.length();i++){
            a[i-1] = int(s[i]) - int('0');
        }
        unlimited_int = a;
    }

    else{
        int n = s.length();
        sign = 1;
        size = n;
        capacity = n;
        int* a = new int[n];
        for (int i=0;i<s.length();i++){
            a[i] = int(s[i]) - int('0');
        }
        unlimited_int = a;
    }
}


UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    size = sz;
    capacity = cap;
    sign = sgn;
    unlimited_int = ulimited_int;
}

UnlimitedInt::~UnlimitedInt(){
    delete [] unlimited_int;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

bool modisequal(UnlimitedInt* i1,UnlimitedInt* i2){
    if (i1->get_size()!=i2->get_size()){
        return false;
    }

    else{
        bool valid = true;
        int* a1 = i1->get_array();
        int* a2 = i2->get_array();
        for (int i=0;i<i1->get_size();i++){
            if (a1[i]!=a2[i]){
                valid = false;
                break;
            }
        }
        
        return valid;
    }
}

bool isgreater(UnlimitedInt* i1,UnlimitedInt* i2){
    if (i1->get_size()>i2->get_size()){
        return true;
    }
    if (i1->get_size()<i2->get_size()){
        return false;
    }
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();

    bool valid = true;

    for (int i=0;i<i1->get_size();i++){
        if (a1[i]>a2[i]){
            break;
        }
        if (a1[i]<a2[i]){
            valid = false;
            break;
        }
    }
    return valid;
}


UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();

    if (sgn1==1 && sgn2==1){
        if (sz1>=sz2){
            string sum = "";
            int j1 = sz1-1;
            int j2 = sz2-1;
            int tempsum = 0;
            int units = 0;
            int carryover = 0;
            while (j2>=0){
                tempsum = a1[j1]+a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%(10);
                sum = std::to_string(units)+sum;
                j1--;
                j2--;
            }

            while (j1>=0){
                tempsum = a1[j1]+carryover;
                carryover = tempsum/10;
                units = tempsum%10;
                sum = std::to_string(units)+sum;
                j1--;
            }

            if (carryover != 0){
                sum = std::to_string(1)+sum;
            }

            UnlimitedInt* U = new UnlimitedInt(sum);
            return U;
        }
        else{
            string sum = "";
            int j1 = sz1-1;
            int j2 = sz2-1;
            int tempsum = 0;
            int units = 0;
            int carryover = 0;
            while (j1>=0){
                tempsum = a1[j1]+a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%(10);
                sum = std::to_string(units)+sum;
                j1--;
                j2--;
            }

            while (j2>=0){
                tempsum = a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%10;
                sum = std::to_string(units)+sum;
                j2--;
            }

            if (carryover != 0){
                sum = std::to_string(1)+sum;
            }

            UnlimitedInt* U = new UnlimitedInt(sum);
            return U;
        }
    }

    else if (sgn1==0 || sgn2==0){
        if(sgn1 == 0){
            return i2;
        }
        else{
            return i1;
        }
    }

    else if (sgn1==-1 && sgn2==-1){
        if (sz1>=sz2){
            string sum = "";
            int j1 = sz1-1;
            int j2 = sz2-1;
            int tempsum=0;
            int units=0;
            int carryover=0;
            while (j2>=0){
                tempsum = a1[j1]+a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%(10);
                sum = std::to_string(units)+sum;
                j1--;
                j2--;
            }

            while (j1>=0){
                tempsum = a1[j1]+carryover;
                carryover = tempsum/10;
                units = tempsum%10;
                sum = std::to_string(units)+sum;
                j1--;
            }

            if (carryover != 0){
                sum = std::to_string(1)+sum;
            }
            
            sum = '-' + sum;

            UnlimitedInt* U = new UnlimitedInt(sum);
            return U;
        }
        else{
            string sum = "";
            int j1 = sz1-1;
            int j2 = sz2-1;
            int tempsum=0;
            int units=0;
            int carryover=0;
            while (j1>=0){
                tempsum = a1[j1]+a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%(10);
                sum = std::to_string(units)+sum;
                j1--;
                j2--;
            }

            while (j2>=0){
                tempsum = a2[j2]+carryover;
                carryover = tempsum/10;
                units = tempsum%10;
                sum = std::to_string(units)+sum;
                j2--;
            }

            if (carryover != 0){
                sum = std::to_string(1)+sum;
            }

            sum = '-'+sum;

            UnlimitedInt* U = new UnlimitedInt(sum);
            return U;
        }
    }

    else{
        if (sgn1==1 && sgn2==-1){
            if (modisequal(i1,i2)){
                UnlimitedInt* I = new UnlimitedInt("0");
                return I;
            }
            
            else if (isgreater(i1,i2)){      //(12,-10)
                string difference = "";
                int j1 = sz1-1;
                int j2 = sz2-1;
                int tempdiff=0;
                int carryover=0;
                while (j2>=0){
                    tempdiff = a1[j1] - carryover - a2[j2];
                    if (tempdiff>=0){
                        carryover = 0;
                    }
                    else{
                        tempdiff+=10;
                        carryover = 1;
                    }
                    j1--;
                    j2--;
                    difference = std::to_string(tempdiff) + difference;
                }

                while (j1>=0){
                    tempdiff = a1[j1] - carryover;
                    if (tempdiff>=0){
                        carryover = 0;
                    }
                    else{
                        tempdiff+=10;
                        carryover = 1;
                    }
                    j1--;
                    difference = std::to_string(tempdiff) + difference;
                }

                UnlimitedInt* U = new UnlimitedInt(difference);
                return U;
            }

            else{
                string difference;
                int j1 = sz1-1;
                int j2 = sz2-1;
                int tempdiff=0;
                int carryover=0;
                while (j1>=0){
                    tempdiff = a2[j2] - carryover - a1[j1];
                    if (tempdiff>=0){
                        carryover = 0;
                    }
                    else{
                        tempdiff+=10;
                        carryover = 1;
                    }
                    j1--;
                    j2--;
                    difference = std::to_string(tempdiff) + difference;
                }

                while (j2>=0){
                    tempdiff = a2[j2] - carryover;
                    if (tempdiff>=0){
                        carryover = 0;
                    }
                    else{
                        tempdiff+=10;
                        carryover = 1;
                    }
                    j2--;
                    difference = std::to_string(tempdiff) + difference;
                }

                difference = '-' + difference;

                UnlimitedInt* U = new UnlimitedInt(difference);
                return U;
            }
        }
    
        else {
            UnlimitedInt* I =  UnlimitedInt::add(i2,i1);
            return I;
        }
    }
}


string UnlimitedInt::to_string(){
    string s = "";
    int n = size;
    for (int i=0;i<n;i++){
        s = s + std::to_string(unlimited_int[i]);
    }
    if (sign == -1){
        s = '-' + s;
    }
    else if(sign == 0){
        s = std::to_string(0);
    }

    return s;
}


UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    string s = i2->to_string();
    if (i2->get_sign() == 1){
        s = '-' + s;
        UnlimitedInt* I = new UnlimitedInt(s);
        return UnlimitedInt::add(i1,I);
    }

    else if (i2->get_sign() == 0){
        return i1;
    }

    else{
        s.erase(s.begin());
        UnlimitedInt* I = new UnlimitedInt(s);
        return UnlimitedInt::add(i1,I);
    }
}


string mull(string i1, int k){
    string p = "";
    int carryover = 0;
    int units = 0;
    int temppro = 0;
    int j = i1.length()-1;
    while (j>=0){
        temppro = k*(int(i1[j])-int('0')) + carryover;
        carryover = temppro/10;
        units = temppro%10;
        p = to_string(units) + p;
        j--;
    }

    if (carryover>0){
        p = to_string(carryover) + p;
    }

    return p;
}

string summ(string s1, string s2){
    int j1;
    int j2;
    if (s1.length()>=s2.length()){
        j1 = s1.length()-1;
        j2 = s2.length()-1;
        string s;
        int carryover = 0;
        int tempsum = 0;
        int units = 0;
        while (j2>=0){
            tempsum = int(s1[j1])-int('0') + int(s2[j2])-int('0') + carryover;
            carryover = tempsum/10;
            units = tempsum%10;
            s = to_string(units) + s;
            j1--;
            j2--;
        }
        while (j1>=0){
            tempsum = int(s1[j1])-int('0') + carryover;
            carryover = tempsum/10;
            units = tempsum%10;
            s = to_string(units) + s;
            j1--;
        }

        if (carryover>0){
            s = to_string(carryover)+s;
        } 
        return s; 
    }
    else{
        j1 = s1.length()-1;
        j2 = s2.length()-1;
        string s;
        int carryover = 0;
        int tempsum = 0;
        int units = 0;
        while (j1>=0){
            tempsum = int(s1[j1])-int('0') + int(s2[j2])-int('0') + carryover;
            carryover = tempsum/10;
            units = tempsum%10;
            s = to_string(units) + s;
            j1--;
            j2--;
        }
        while (j2>=0){
            tempsum = int(s2[j2])-int('0') + carryover;
            carryover = tempsum/10;
            units = tempsum%10;
            s = to_string(units) + s;
            j2--;
        }

        if (carryover>0){
            s = to_string(carryover)+s;
        } 
        return s;
    }

    

}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt*i1, UnlimitedInt* i2){
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    if (sgn1*sgn2 == 0){
        UnlimitedInt* U = new UnlimitedInt("0");
        return U;
    }
    else{
        if (sgn1==1 and sgn2 == 1){
            string temppro = "";
            int units = 0;
            string p = "";
            string s2 = i2->to_string();
            string s1 = i1->to_string();
            int j = s2.length()-1;
            while (j>=0){
                units = int(s2[j])-int('0');
                temppro = mull(s1,units);
                for (int k=0;k<s2.length()-1-j;k++){
                temppro = temppro + '0';
                }
                p = summ(p,temppro);
                j--;
            }
            UnlimitedInt* U = new UnlimitedInt(p);
            return U;
        }
        else{
            if (sgn1 == 1 && sgn2 == -1){
                string temppro = "";
                int units = 0;
                string p = "";
                string s2 = i2->to_string();
                s2.erase(s2.begin());
                string s1 = i1->to_string();
                int j = s2.length()-1;
                while (j>=0){
                    units = int(s2[j])-int('0');
                    temppro = mull(s1,units);
                    for (int k=0;k<s2.length()-1-j;k++){
                    temppro = temppro + '0';
                    }   
                    p = summ(p,temppro);
                    j--;
                }
                p = '-' + p;
                UnlimitedInt* U = new UnlimitedInt(p);
                return U;
            }

            else if (sgn1 == -1 && sgn2 == 1){
                string temppro = "";
                int units = 0;
                string p = "";
                string s2 = i2->to_string();
                string s1 = i1->to_string();
                s1.erase(s1.begin());
                int j = s2.length()-1;
                while (j>=0){
                    units = int(s2[j])-int('0');
                    temppro = mull(s1,units);
                    for (int k=0;k<s2.length()-1-j;k++){
                    temppro = temppro + '0';
                    }   
                    p = summ(p,temppro);
                    j--;
                }
                p = '-' + p;
                UnlimitedInt* U = new UnlimitedInt(p);
                return U;
            }

            else{
                string temppro = "";
                int units = 0;
                string p = "";
                string s2 = i2->to_string();
                string s1 = i1->to_string();
                s1.erase(s1.begin());
                s2.erase(s2.begin());
                int j = s2.length()-1;
                while (j>=0){
                    units = int(s2[j])-int('0');
                    temppro = mull(s1,units);
                    for (int k=0;k<s2.length()-1-j;k++){
                    temppro = temppro + '0';
                    }   
                    p = summ(p,temppro);
                    j--;
                }
                UnlimitedInt* U = new UnlimitedInt(p);
                return U;
            }
        }     
    } 
}


string diff(string s1,string s2){
    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);
    int tempdiff = 0;
    string d = "";
    int carryover = 0;
    int j1 = s1.length()-1;
    int j2 = s2.length()-1;
    while (j2>=0){
        tempdiff = int(s1[j1])  - int(s2[j2]) - carryover;
        if (tempdiff<0){
            tempdiff+=10;
            carryover = 1;
        }
        else{
            carryover = 0;
        }
        d = to_string(tempdiff) + d;
        j1--;
        j2--;
    }

    while (j1>=0){
        tempdiff = int(s1[j1]) - int('0') - carryover;
        if (tempdiff<0){
            carryover = 1;
            tempdiff+=10;
        }
        else{
            carryover = 0;
        }
        d = to_string(tempdiff) + d;
        j1 --;
    }
    return d;

}

bool isgreaterthan(string s1,string s2){
    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);

    if (s1.length()<s2.length()){
        return false;
    }

    else if (s1.length()>s2.length()){
        return true;
    }

    else{
        bool valid = true;
        for (int i=0;i<s1.length();i++){
            int a1 = int(s1[i]) - int('0');
            int a2 = int(s2[i]) - int('0');
            if (a1>a2) break;
            else if (a1<a2){
                valid = false;
                break;
            }
        }
        return valid;
    }
}

bool isequalto(string s1,string s2){

    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);

    if (s1.length()!= s2.length()){
        return false;
    }
    else{
        bool valid = true;
        for (int i=0;i<s1.length();i++){
            int a1 = int(s1[i]) - int('0');
            int a2 = int(s2[i]) - int('0');
            if (a1!= a2){
                valid = false;
                break;
            }
        }
        return  valid;
    }
}

string longDivision(string i1, int i2)
{
    string ans;
  
    int idx = 0;
    int temp = i1[idx] - '0';
    while (temp < i2)
        temp = temp * 10 + (i1[++idx] - '0');
  
    while (i1.size() > idx) {
        ans += (temp / i2) + '0';
  
        temp = (temp % i2) * 10 + i1[++idx] - '0';
    }
  
    if (ans.length() == 0)
        return "0";
  
    return ans;
}

string diff2(string s1,string s2){
    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);
    int tempdiff = 0;
    string d = "";
    int carryover = 0;
    int j1 = s1.length()-1;
    int j2 = s2.length()-1;
    while (j2>=0){
        tempdiff = int(s1[j1])  - int(s2[j2]) - carryover;
        if (tempdiff<0){
            tempdiff+=10;
            carryover = 1;
        }
        else{
            carryover = 0;
        }
        d = to_string(tempdiff) + d;
        j1--;
        j2--;
    }

    while (j1>=0){
        tempdiff = int(s1[j1]) - int('0') - carryover;
        if (tempdiff<0){
            carryover = 1;
            tempdiff+=10;
        }
        else{
            carryover = 0;
        }
        d = to_string(tempdiff) + d;
        j1 --;
    }
    return d;

}

bool isgreaterthan2(string s1,string s2){
    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);

    if (s1.length()<s2.length()){
        return false;
    }

    else if (s1.length()>s2.length()){
        return true;
    }

    else{
        bool valid = true;
        for (int i=0;i<s1.length();i++){
            int a1 = int(s1[i]) - int('0');
            int a2 = int(s2[i]) - int('0');
            if (a1>a2) break;
            else if (a1<a2){
                valid = false;
                break;
            }
        }
        return valid;
    }
}

bool isequalto2(string s1,string s2){

    int id = 0;
    while (s1[id] == '0'){
        id++;
    }
    s1.erase(0,id);

    id = 0;
    while (s2[id] == '0'){
        id++;
    }
    s2.erase(0,id);

    if (s1.length()!= s2.length()){
        return false;
    }
    else{
        bool valid = true;
        for (int i=0;i<s1.length();i++){
            int a1 = int(s1[i]) - int('0');
            int a2 = int(s2[i]) - int('0');
            if (a1!= a2){
                valid = false;
                break;
            }
        }
        return  valid;
    }
}

int wil(string s1,string s2){
    
    if (isequalto2(mull(s2,1),s1)){
        return 1;
    }
    if (isgreaterthan2(mull(s2,1),s1)){
        return 0;
    }
    else if (isequalto2(mull(s2,2),s1)){
        return 2;
    }
    else if (isequalto2(mull(s2,3),s1)){
        return 3;
    }
    else if (isequalto2(mull(s2,4),s1)){
        return 4;
    }
    else if (isequalto2(mull(s2,5),s1)){
        return 5;
    }
    else if (isequalto2(mull(s2,6),s1)){
        return 6;
    }
    else if (isequalto2(mull(s2,7),s1)){
        return 7;
    }
    else if (isequalto2(mull(s2,8),s1)){
        return 8;
    }
    else if (isequalto2(mull(s2,9),s1)){
        return 9;
    }
    else if (isgreaterthan2(mull(s2,2),s1)){
        return 1;
    }
    else if (isgreaterthan2(mull(s2,3),s1)){
        return 2;
    }
    else if (isgreaterthan2(mull(s2,4),s1)){
        return 3;
    }
    else if (isgreaterthan2(mull(s2,5),s1)){
        return 4;
    }
    else if (isgreaterthan2(mull(s2,6),s1)){
        return 5;
    }
    else if (isgreaterthan2(mull(s2,7),s1)){
        return 6;
    }
    else if (isgreaterthan2(mull(s2,8),s1)){
        return 7;
    }
    else if (isgreaterthan2(mull(s2,9),s1)){
        return 8;
    }
    else if (isgreaterthan2(mull(s2,10),s1)){
        return 9;
    }

}


string divv(string s1,string s2){
    if (!isgreaterthan2(s1,s2)){
        return "0";
    }
    else{
        string q = "0";
        int n = s2.length();
        string t = "";
        for (int i=0;i<n;i++){
            t += s1[i];
        }
        int k = n;
        int qt = 0;
        while (k<=s1.length()){
            qt = wil(t,s2);
            q = q + to_string(qt);
            t = diff2(t,mull(s2,qt));
            t = t + s1[k];
            k++;
        }
        return q;
    }
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    string q = "0";
    string s1 = i1->to_string();
    string s2 = i2->to_string();
    int sgn1 = i1->get_sign();
    int sgn2 = i2->get_sign();
    if (sgn1 == 1 && sgn2 == 1){
        // while (isgreaterthan(s1,s2)){
        //     q = summ(q,"1");
        //     s1 = diff(s1,s2);
        // }
        q = divv(s1,s2);
        UnlimitedInt* U = new UnlimitedInt(q);
        return U; 
    }

    else if (sgn1 == -1 && sgn2 == -1){
        s1.erase(s1.begin());
        s2.erase(s2.begin());
        // while (isgreaterthan(s1,s2)){
        //     q = summ(q,"1");
        //     s1 = diff(s1,s2);
        // }
        q = divv(s1,s2);
        UnlimitedInt* U = new UnlimitedInt(q);
        return U;
    }

    else if (sgn1 == 0){
        UnlimitedInt* U = new UnlimitedInt("0");
        return U;
    }

    else{
        if (sgn1 == 1 && sgn2 == -1){
            s2.erase(s2.begin());
            // while (isgreaterthan(s1,s2)){
            //     q = summ(q,"1");
            //     s1 = diff(s1,s2);
            // }
            q = divv(s1,s2);
            UnlimitedInt* Q = new UnlimitedInt(q);
            UnlimitedInt* d = new UnlimitedInt(s2);
            Q = UnlimitedInt::mul(Q,d);
            s1 = diff(s1,Q->to_string());
            if (isequalto(s1,"0")){
                q = '-' + q;
            }
            else{
                q = summ(q,"1");
                q = '-' + q;
            }
            UnlimitedInt* U = new UnlimitedInt(q);
            return U;
        }

        else{
            s1.erase(s1.begin());
            // while (isgreaterthan(s1,s2)){
            //     q = summ(q,"1");
            //     s1 = diff(s1,s2);
            // }
            q = divv(s1,s2);
            UnlimitedInt* Q = new UnlimitedInt(q);
            UnlimitedInt* d = new UnlimitedInt(s2);
            Q = UnlimitedInt::mul(Q,d);
            s1 = diff(s1,Q->to_string());
            if (isequalto(s1,"0")){
                q = '-' + q;
            }
            else{
                q = summ(q,"1");
                q = '-' + q;
            }
            UnlimitedInt* U = new UnlimitedInt(q);
            return U;
        }
    }
    
    
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){

    UnlimitedInt* t = UnlimitedInt::div(i1,i2);
    t = UnlimitedInt::mul(t,i2);
    t = UnlimitedInt::sub(i1,t);

    if (t->to_string()[0] == '-'){
        t = UnlimitedInt::sub(t,i2);
    }
    return t;
    
}

