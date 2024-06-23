#include <iostream>
#include <vector>
#include <cerrno>
#include <assert.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#define PLAYERCOUNT 3
#define CARDSCOUNT 54
#define CURRENTPLAYER 0
#define VALUECOUNT 17
#define ERROR -1

using namespace std;
const char toFigure[]="34567890JQKA 2YZ";
enum COLOR{  //��ɫ��ʾASCII: 3~6
    eHEART=3,//���� 
    eDIAMOND,//��Ƭ 
    eCLUB,   //�ݻ� 
    eSPADE   //���� 
};

class Card;
class CardsType;
class CardGroup;
class Player;
class Landlords;
class LastCards;
bool makeChoice(string tip);
bool cmp(Card* a,Card* b);

class Card{
  public:
	char figure;
    COLOR color;
    int value;
    Card(char _figure,COLOR _color){
        figure=_figure;
        color=_color;
        value=calValue();
    }
    int calValue(){
        for(int i=0;toFigure[i];i++){
            if(toFigure[i]==figure){
                return i;
            }
        }
        return ERROR;
    }
    void print(){
        assert(value!=ERROR);
        if(figure=='Z'){
            cout<<"ZZ";
        }else if(figure=='Y'){
        	cout<<"YY";
        }else{
            cout<<figure<<(char)color;
        }
        cout<<' ';
    }
};

class CardsType{
  public:
    //Ϊ�˹淶���Ҷ�Ӧ�Ƶķ���
    //ͳһΪ3������cnt1��isContinuous��cnt2
    int typeId;
    string typeStr;
    int cnt1,cnt2;
    bool isContinuous;
    CardsType(){
        typeId=ERROR;
    }
    bool operator ==(const CardsType& other)const{
        return this->typeId==other.typeId;
    }
    void init(char* _typeStr,int _typeId,int _cnt1,bool _isContinuous,int _cnt2){
        cnt1=_cnt1;
        isContinuous=_isContinuous;
        cnt2=_cnt2;
        typeStr=_typeStr;
        typeId=_typeId;
    }
}; 

class CardGroup{
  public:
    vector<Card*> cards;
    CardsType type;
    void calType(){
        int i,n=cards.size();
        //init(typeStr,typeId,cnt1,isContinuous,cnt2)
        if(n==0){
            type.init("����",14,0,0,0);
            return;
        }
        if(n==2&&cards[0]->value==15&&cards[1]->value==14){
            type.init("��ը",0,0,0,0);
            return;
        }
        //ͳ��ͬ�������ж����� 
        int cntFlag[VALUECOUNT]={0};
        for(i=0;i<n;i++){
            cntFlag[cards[i]->value]++;
		}
		//ͳ�Ƶ����������ٵ��� 
        int maxCnt=0,minCnt=4;
        for(i=0;i<VALUECOUNT;i++){ 
            if(maxCnt<cntFlag[i]){
               maxCnt=cntFlag[i];
            }
            if(cntFlag[i]&&minCnt>cntFlag[i]){
               minCnt=cntFlag[i];
            }
        }
        if(n==4&&maxCnt==4){
            type.init("ըdan",1,4,0,0);
            return;
        }
        if(n==1){
            type.init("����",2,1,0,0);
            return;
        }
        if(n==2&&maxCnt==2){
            type.init("����",3,2,0,0);
            return;
        }
        if(n==3&&maxCnt==3){
            type.init("���� ",4,3,0,0);
            return;
        }
        if(n==4&&maxCnt==3){
            type.init("����һ",5,3,0,1);
            return;
        }
        if(n==5&&maxCnt==3&&minCnt==2){
            type.init("����һ��",6,3,0,2);
            return;
        }
        if(n==6&&maxCnt==4){
            type.init("�Ĵ���",7,4,0,1);
            return;
        }
        if(n==8&&maxCnt==4&&minCnt==2){
            type.init("�Ĵ���",8,4,0,2);
            return;
        } 
        if(n>=5&&maxCnt==1&&cards[0]->value==cards[n-1]->value+n-1){
            type.init("˳��",9,1,1,0);
            return;
        }
        if(n>=6&&maxCnt==2&&minCnt==2&&cards[0]->value==cards[n-1]->value+n/2-1){
            type.init("����",10,2,1,0); 
            return;
        }
        int fjCnt;//ͳ�������Ҵ���3���ŵ��� 
        for(i=0;i<VALUECOUNT &&cntFlag[i]<3;i++);
        for(fjCnt=0;i<VALUECOUNT &&cntFlag[i]>=3;i++,fjCnt++);
        if(fjCnt>1){
            if(n==fjCnt*3)
                type.init("�ɻ�",11,3,1,0);
            else if(n==fjCnt*4)
                type.init("�ɻ�",12,3,1,1); 
            else if(n==fjCnt*5&&minCnt==2)
                type.init("�ɻ�",13,3,1,2); 
        }
    }
    void init(string inputStr, vector<Card*> &cardsHolded){
        this->cards.clear();
        //���� 
        if(inputStr=="N"){
            this->calType();
            return;
        }
        int i,j;
        //����Ϸ����ж� 
        for(i=0;i<inputStr.size();i++){
            bool find=false;
            for(j=0;toFigure[j];j++){ 
                if(inputStr[i]==toFigure[j]){
                    find=true;
                    break;
                }
            } 
            if(find==false){
                //�����ַ�����toFigure��
                return;
            }
        }
        //����������û����Щ�� 
        int visitFlag[20]={0};
        for(i=0;i<inputStr.size();i++){
            Card *find=NULL;
            for(j=0;j<cardsHolded.size();j++){
                if(!visitFlag[j]&&cardsHolded[j]->figure==inputStr[i]){
					visitFlag[j]=1;
                    find=cardsHolded[j];
                    break;
                }
            }
            if(find){
                this->cards.push_back(find);
            }else{
                cout<<inputStr[i];
                cout<<"û���ҵ�\t";
                this->cards.clear();
                return;
            }
        }//end for(i=0;i<inputStr.size();i++) 
        this->arrange();
    }
    void init(vector<Card*> newCards){
		this->cards=newCards;
        this->arrange();
	}
    bool isCanBeat(CardGroup &cardGroup){
        if(cardGroup.type.typeStr=="��ը"){
            return false;
        }else if(this->type.typeStr=="��ը"){
            return true;
        }else if(cardGroup.type==this->type &&this->type.typeStr=="ըdan"){
            return value()>cardGroup.value();
        }else if(cardGroup.type.typeStr=="ըdan"){
            return false;
        }else if(this->type.typeStr=="ըdan"){
            return true;
        }else if(cardGroup.type==this->type &&this->cards.size()==cardGroup.cards.size()){
            return this->value()>cardGroup.value();
        }else{
            return false;
        }
    }
    int value(){
        //��������Ȩֵ 
        int i;
        if(type.typeStr=="����һ"||type.typeStr=="����һ��"||type.typeStr=="�ɻ�"){
            for(i=2;i<cards.size();i++){
                if(cards[i]->value==cards[i-2]->value){
                    return cards[i]->value;
                }
            }
        }
        if(type.typeStr=="�Ĵ���"){
            for(i=3;i<cards.size();i++){
                if(cards[i]->value==cards[i-3]->value){
                    return cards[i]->value;
                }
            }
        }
        return cards[0]->value;
    }
    void arrange(){
        //�������򡢼������� 
        sort(this->cards.begin(),this->cards.end(),cmp);
        this->calType();
    }
};
class LastCards{
	static LastCards *lastCards;
  public:
    Player *player;
    CardGroup cardGroup;
    static LastCards* inst(){//����ģʽ 
		if(lastCards==NULL){
			lastCards=new LastCards();
        }
		return lastCards;
	}
    vector<Card*> findCanBeatFrom(vector<Card*> &cardsHolded){
        //�����ܴ�ù����� 
        int i,j,k,n=cardsHolded.size(),m=cardGroup.cards.size();
        string typeStr=cardGroup.type.typeStr;
        vector<Card*> ret;
        if(typeStr=="��ը"||n<m){
            //�򲻹������ؿ����� 
            return ret;
        }
        int value=cardGroup.value();
        //ͳ�Ƹ����Ƴ��ֵĴ��� 
        int cntFlag[VALUECOUNT]={0};
        for(i=0;i<n;i++){ 
            cntFlag[cardsHolded[i]->value]++;
        } 
        int continuousCount=1;
        if(cardGroup.type.isContinuous){
            continuousCount=m/(cardGroup.type.cnt1+cardGroup.type.cnt2);
        }
        bool findFirstFigure;
        //cout<<"continuousCount="<<continuousCount<<endl;
        for(i=value+1;i<VALUECOUNT;i++){
            findFirstFigure=true;
            for(j=0;j<continuousCount;j++){ 
                if(cntFlag[i-j]<cardGroup.type.cnt1){
                    findFirstFigure=false;
                    break;
                }
            }
            if(findFirstFigure){
                ret.clear();
                int firstFigure=i;
                //cout<<"����"<<cardGroup.type.cnt1<<"��"<<firstFigure+3<<endl;
                for(k=0,j=0;k<cardsHolded.size() &&j<continuousCount;k++){ 
                    if(cardsHolded[k]->value==firstFigure-j){
                        for(int kk=0;j>=0&&kk<cardGroup.type.cnt1;kk++){ 
                            ret.push_back(cardsHolded[k+kk]);
                        } 
                        j++; 
                    }
                } 
                if(cardGroup.type.cnt2>0){
                    int SecondFigures[5];
                    int SecondCount=continuousCount;
                    if(cardGroup.type.typeStr=="�Ĵ���")
                        SecondCount=2;
                    bool findSecondFigure=true;
                    for(j=0,k=-1;j<SecondCount &&findSecondFigure;j++){
                        findSecondFigure=false;
                        for(k++;k<VALUECOUNT;k++){
                            SecondFigures[j]=k;
                            if(cntFlag[k]>=cardGroup.type.cnt2 &&cntFlag[k]<cardGroup.type.cnt1){
                                findSecondFigure=true;
                                break;
                            }
                        }
                    }
                    if(findSecondFigure){
                        //cout<<"����SecondFigure "<<cardGroup.type.cnt2<<"��"<<SecondFigures[0]+3<<endl;
                        //cout<<"SecondCount= "<<SecondCount<<endl;
                        //for(i=0;i<SecondCount;i++)cout<<"SecondFigures["<<i<<"]="<<SecondFigures[i]<<endl;
                        for(i=0;i<SecondCount;i++){ 
                            for(j=0;j<cardsHolded.size();){ 
                                if(cardsHolded[j]->value==SecondFigures[i]){
                                    for(k=0;k<cardGroup.type.cnt2;k++){
                                        //cout<<"���"<<cardsHolded[j]->value+3<<endl;
                                        ret.push_back(cardsHolded[j+k]);
                                    }
                                    do{
                                        j++;
                                    }while(j<cardsHolded.size()&&cardsHolded[j]->value==SecondFigures[i]);
                                }else{
                                    j++;
                                } 
                            }
                        } 
                        return ret;
                    }//if(findSecondFigure) 
                }//end if(cardGroup.type.cnt2>0)
                else{
                    return ret;
                }
            }//end if(findFirstFigure)
        }//end for(i=value+1;i<VALUECOUNT;i++)
        ret.clear();
        //û�ƴ�ù�ʱ������û��ըdan 
        if(typeStr!="ըdan"){
            for(i=cardsHolded.size()-1;i>=3;i--){
                if(cardsHolded[i]->value==cardsHolded[i-3]->value){
                    for(j=0;j<4;j++){
                        ret.push_back(cardsHolded[i-j]);
                    }
                    break;
                }
            }
        }
        return ret;   
    }//end vector<Card*> findCanBeatFrom()
};
LastCards* LastCards::lastCards = NULL;

class Player{
  public:
    string name;
    vector<Card*> cards;
    void arrange(){
        sort(cards.begin(),cards.end(),cmp);
    }
    void print(){
        cout<<this->name<<":\t";
        for(int i=0;i<cards.size();i++){
            cards[i]->print();
        }
        cout<<"["<<cards.size()<<"]\n";
    }
    vector<Card*> tip(){
        //��ʾ����,ʹ�Լ���Сһ�����
        CardGroup ret;
        string temp;
        int j,k,m=cards.size();
        for(j=0;j<m;j++){
            temp="";
            for(k=j;k<m;k++){
                temp+=cards[k]->figure;
            }
            ret.init(temp,cards);
            if(ret.type.typeId!=ERROR){
                return ret.cards;
            }
        }
        ret.cards.clear();
        return ret.cards;
    }
    void chupai(CardGroup &cardGroup){
        //���� 
        cout<<this->name<<":\t";
        cout<<cardGroup.type.typeStr<<' ';
        for(int i=0;i<cardGroup.cards.size();i++){
            cardGroup.cards[i]->print();
            this->cards.erase(find(this->cards.begin(),this->cards.end(),cardGroup.cards[i])); 
        }
        cout<<"\t["<<this->cards.size()<<"]\n";
        if(cardGroup.type.typeStr!="����"){
            //��¼�� LastCards �� 
            LastCards::inst()->player=this;
            LastCards::inst()->cardGroup.init(cardGroup.cards);
        }
    }
};

class Landlords{
    Player *player[PLAYERCOUNT];
    bool finished,youWin,landlordWin;
    int landlordIndex;
    Card *cards[CARDSCOUNT];
  public:
    Landlords(){
        int i,j,k;
        for(i=0;i<PLAYERCOUNT;i++){
            this->player[i]=new Player();
        }
        //54���Ƴ�ʼ�� 
        for(k=i=0;i<14;i++){
            if(toFigure[i]==' '){
                continue;
            }
            for(COLOR color=eHEART;color<=eSPADE;color=(COLOR)(color+1)){
                this->cards[k++]=new Card(toFigure[i],color);
            }
        }
        this->cards[k++]=new Card('Y',eSPADE);
        this->cards[k]=new Card('Z',eHEART);
    }
    ~Landlords(){
        for(int i=0;i<PLAYERCOUNT;i++){
            delete this->player[i];
        }
        for(int i=0;i<CARDSCOUNT;i++){
            delete this->cards[i];
        }
    } 
    void init(){
        player[CURRENTPLAYER]->name="Bice";
        player[1]->name="���2";
        player[2]->name="���3";
        finished=false;
        youWin=false;
        landlordWin=false;
        //������
        landlordIndex=ERROR; 
        while(landlordIndex==ERROR){
            srand((int)time(0));
            shuffle();
            landlordIndex=chooseLandlord();
        }
        cout<<player[landlordIndex]->name<<"\t��Ϊ����\n\n";
        this->add3Cards();
        LastCards::inst()->player=player[landlordIndex];
    }
    void startGame(){
        string inputSrt;
        CardGroup inputCards;
        for(int iTurns=landlordIndex;!finished;iTurns++){
            if(iTurns>=PLAYERCOUNT){
                iTurns=0;
            }
            if(iTurns==CURRENTPLAYER){
                cout<<endl;
                player[iTurns]->print();
                cout<<"������ʾ��Z=���� Y=С�� 0=10 N=���� ��������� ����:JKQ0A9\n����ƣ�\t";
                do{
                    cin>>inputSrt;
                    inputCards.init(inputSrt,player[iTurns]->cards);
                }while(check(&inputCards)==false);
            }else{
                if(player[iTurns]==LastCards::inst()->player){
                    //�����ϴγ��Ƶ����Լ���������ʾ���� 
                    inputCards.init(player[iTurns]->tip());
                }else{
                    //�����ܴ�ù��ϼҵ��� 
                    inputCards.init(LastCards::inst()->findCanBeatFrom(player[iTurns]->cards));
                }
            }
            player[iTurns]->chupai(inputCards);//���� 
            
            if(player[iTurns]->cards.size()==0){
                //�������û���ˣ���Ϸ���� 
                finished=true;
                landlordWin=iTurns==landlordIndex;
                if(landlordWin){
                    youWin=landlordIndex==CURRENTPLAYER;
                }else{
                    youWin=landlordIndex!=CURRENTPLAYER;
                }
            }
        }
        cout<<"\n_________________________ "<<(youWin?"You Win!":"You Lose!")<<" _________________________\n\n";
    }
    void add3Cards(){
        cout<<"����3����:\t";
        for(int i=PLAYERCOUNT*17;i<CARDSCOUNT;i++){
            this->cards[i]->print();
            player[landlordIndex]->cards.push_back(cards[i]);
        }
        cout<<endl;
        player[landlordIndex]->arrange();
    }
    int chooseLandlord(){
        cout<<"\n_________________________ ������ _________________________\n\n";
        int first=-1,last,cnt=0,i,j=rand()%PLAYERCOUNT;
        bool decision;
        for(i=0;i<PLAYERCOUNT;i++,j==2?j=0:j++){
            if(j==CURRENTPLAYER){
                decision=makeChoice("�Ƿ���������(Y=��/N=����):");
            }else{ 
                decision=rand()%2;
            }
            if(decision){
                cnt++;
                last=j;
                if(first==-1){
                    first=j;
                }
                cout<<this->player[j]->name<<"\t������\n";
            }else{
                cout<<this->player[j]->name<<"\tû����\n";
            }
        }
        if(cnt==0){
            cout<<"û���������·���\n";
            return ERROR;
        }
        if(cnt==1){
            //��һ��ֻ��һ�������� 
            return first;
        }
        else{
            //���һ������ 
            if(first==CURRENTPLAYER){
                decision=makeChoice("�Ƿ���������(Y=��/N=����):");
            }else{
                decision=rand()%2;
            }
            if(decision){
                cout<<this->player[first]->name<<"\t������\n";
                return first;
            }else{
                cout<<this->player[first]->name<<"\tû����\n";
                return last;
            }
        }
    }
    void shuffle(){
        int i,j,k;    
        //ϴ�� 
        for(i=0;i<CARDSCOUNT;i++){
            swap(this->cards[i],this->cards[rand()%CARDSCOUNT]);
        }
        
        //���� 
        for(k=i=0;i<PLAYERCOUNT;i++){
            this->player[i]->cards.clear();
            for(j=0;j<17;j++){
                this->player[i]->cards.push_back(this->cards[k++]);
            }
            this->player[i]->arrange();//���� 
            this->player[i]->print();
        }
    }
    bool check(CardGroup *cardGroup){
        if(cardGroup->type.typeId==ERROR){
            cout<<"���ƴ�����������\n";
            return false;
        }else if(cardGroup->type.typeStr=="����"){
            return true;
        }else if(LastCards::inst()->player!=player[CURRENTPLAYER]&&!cardGroup->isCanBeat(LastCards::inst()->cardGroup)){
            cout<<"�򲻹�����������\n";
            return false;
        }else{
            return true;
        }
    }
};

int main(){
    Landlords *landlords=new Landlords();
    do{
        landlords->init();//���ơ������� 
        landlords->startGame();//��Ϸ��ʼ 
    }while(makeChoice("\n�Ƿ������Ϸ����Y=����/N=������: "));
    delete landlords;
    return 0;
}

bool makeChoice(string tip){
    cout<<tip;
    string input;
    cin>>input;
    return input=="Y"||input=="y";
}

bool cmp(Card* a,Card* b){
    //�Ƚ������ƴ�С 
    if(a->value==b->value){
        return a->color>b->color;
    }else{
        return a->value>b->value;
    }
}

