/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"
string diff1(string s1,string s2){
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


bool isgreaterthan1(string s1,string s2){
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

bool isequalto1(string s1,string s2){

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

string gcd(string i1, string i2){
    string s1 = i1;
    string s2 = i2;
    while (!isequalto1(s1,s2)){
        if (isgreaterthan1(s1,s2)){
            s1 = diff1(s1,s2);
        }
        else{
            s2 = diff1(s2,s1);
        }
    }
    return s1;
}

string gcdd(string s1,string s2){
    UnlimitedInt* I1 = new UnlimitedInt(s1);
    UnlimitedInt* I2 = new UnlimitedInt(s2);
    while (!isequalto1(s1,s2) && !isequalto1(s1,"0") && !isequalto1(s2,"0")){
        if (isgreaterthan1(s1,s2)){
            I1 = UnlimitedInt::mod(I1,I2);
            s1 = I1->to_string();
        }
        else{
            I2 = UnlimitedInt::mod(I2,I1);
            s2 = I2->to_string();
        }
    }
    if (isequalto1(s1,"0")){
        return s2;
    }
    if (isequalto1(s2,"0")){
        return s1;
    }

    return s1;
    delete I1;
    delete I2;

    
}


UnlimitedRational::UnlimitedRational(UnlimitedInt* num,UnlimitedInt* den){
    int sgn1 = num->UnlimitedInt::get_sign();
    int sgn2 = den->UnlimitedInt::get_sign();
    string s1 = num->UnlimitedInt::to_string();
    string s2 = den->UnlimitedInt::to_string();

    if (sgn1==1 && sgn2 == 1){
        string g = gcdd(s1,s2);
        UnlimitedInt* t = new UnlimitedInt(g);
        p = UnlimitedInt::div(num,t);
        q = UnlimitedInt::div(den,t);
    }

    else if (sgn1==1 && sgn2==-1){
        s2.erase(s2.begin());
        string g = gcdd(s1,s2);
        UnlimitedInt* t = new UnlimitedInt(g);
        p = UnlimitedInt::div(num,t);
        q = UnlimitedInt::div(den,t);
    }

    else if (sgn1==-1 && sgn2==1){
        s1.erase(s1.begin());
        string g = gcdd(s1,s2);
        UnlimitedInt* t = new UnlimitedInt(g);
        p = UnlimitedInt::div(num,t);
        q = UnlimitedInt::div(den,t);
    }

    else if (sgn1==-1 && sgn2==-1){
        s1.erase(s1.begin());
        s2.erase(s2.begin());
        string g = gcdd(s1,s2);
        UnlimitedInt* t = new UnlimitedInt(g);
        p = UnlimitedInt::div(num,t);
        q = UnlimitedInt::div(den,t);
    }

    else if (sgn1==0 && sgn2!=0){
        UnlimitedInt* i1 = new UnlimitedInt("0");
        UnlimitedInt* i2 = new UnlimitedInt("1");
        p = i1;
        q = i2;
    }

    else{
        UnlimitedInt* i1 = new UnlimitedInt("0");
        UnlimitedInt* i2 = new UnlimitedInt("0");
        p = i1;
        q = i2;
    }
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->UnlimitedInt::to_string();
}

string UnlimitedRational::get_q_str(){
    return q->UnlimitedInt::to_string();
}

string UnlimitedRational::get_frac_str(){
    string s = p->UnlimitedInt::to_string() + "/" + q->UnlimitedInt::to_string();
    return s;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();
    if (q1->get_sign() * q2->get_sign() == 0){
        UnlimitedInt* n = new UnlimitedInt("1");
        UnlimitedInt* d = new UnlimitedInt("0");
        UnlimitedRational* r = new UnlimitedRational(n,d);
        return r;
    }
    else{
        UnlimitedInt* p3 = UnlimitedInt::add(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
        UnlimitedInt* q3 = UnlimitedInt::mul(q1,q2);
        UnlimitedRational* r = new UnlimitedRational(p3,q3);
        return r;
    }
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();
    if (q1->get_sign() * q2->get_sign() == 0){
        UnlimitedInt* n = new UnlimitedInt("1");
        UnlimitedInt* d = new UnlimitedInt("0");
        UnlimitedRational* r = new UnlimitedRational(n,d);
        return r;
    }
    else{
        UnlimitedInt* p3 = UnlimitedInt::sub(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
        UnlimitedInt* q3 = UnlimitedInt::mul(q1,q2);
        UnlimitedRational* r = new UnlimitedRational(p3,q3);
        return r;
    }
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();
    if (q1->get_sign() * q2->get_sign() == 0){
        UnlimitedInt* n = new UnlimitedInt("1");
        UnlimitedInt* d = new UnlimitedInt("0");
        UnlimitedRational* r = new UnlimitedRational(n,d);
        return r;
    }
    else{
        UnlimitedInt* p3 = UnlimitedInt::mul(p1,p2);
        UnlimitedInt* q3 = UnlimitedInt::mul(q1,q2);
        UnlimitedRational* r = new UnlimitedRational(p3,q3);
        return r;
    }
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();
    if (q1->get_sign() * q2->get_sign() == 0){
        UnlimitedInt* n = new UnlimitedInt("1");
        UnlimitedInt* d = new UnlimitedInt("0");
        UnlimitedRational* r = new UnlimitedRational(n,d);
        return r;
    }
    else{
        UnlimitedInt* p3 = UnlimitedInt::mul(p1,q2);
        UnlimitedInt* q3 = UnlimitedInt::mul(p2,q1);
        UnlimitedRational* r = new UnlimitedRational(p3,q3);
        return r;
    }
}

