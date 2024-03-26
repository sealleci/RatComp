#include <bits/stdc++.h>
#include <direct.h>
using namespace std;

struct word {
	string k;
	string v;
	word() {}
	word(string k_, string v_): k(k_), v(v_) {}
	bool operator == (const string &key) {
		return (this->k == key);
	}
};

struct gram {
	string l;
	vector<string> r;
	gram() {}
	gram(string l_) {
		this->l = l_;
	}
	bool operator == (const string &left) {
		return (this->l == left);
	}
	bool operator == (const gram &b) {
		if(this->l!=b.l){
			return false;
		}
		if((int)this->r.size()!=(int)b.r.size()){
			return false;
		}
		for(int i=0;i<(int)this->r.size();++i){
			if(this->r[i]!=b.r[i]){
				return false;
			}
		}
		return true;
	}
	void output(){
		cout<<this->l<<" -> ";
		for(auto e:r){
			cout<<e;
		}
		cout<<endl;
	}
};
inline bool gramCmp(const gram& a, const gram& b) {
	string ar="",br="";
	for(auto e:a.r){
		ar+=e;
	}
	for(auto e:b.r){
		br+=e;
	}
	if(a.l!=b.l){
		return (a.l < b.l);
	}else{
		return ar<br;
	}
}

struct ffset
{
	string l;
	set<string> FIRST;
	set<string> FOLLOW;
	ffset() {}
	ffset(string l_) {
		this->l = l_;
	}
	bool operator == (const string &left) {
		return (this->l == left);
	}
};

struct select
{
	string l;
	vector<string> r;
	set<string> SELECT;
	select() {}
	select(string l_) {
		this->l = l_;
	}
	bool operator == (const string &left) {
		return (this->l == left);
	}
};

struct parseGrid
{
	int vnCnt;
	int vtCnt;
	set<string> vns;
	set<string> vts;
	int** grid;
	int isCreated = 0;
	parseGrid() {}
	parseGrid(const set<string>& vn, const set<string>& vt) {
		this->vnCnt = vn.size();
		this->vtCnt = vt.size();
		for (string e : vn) {
			this->vns.insert(e);
		}
		for (string e : vt) {
			this->vts.insert(e.substr(1, e.length() - 2));
		}

		this->grid = new int*[this->vnCnt + 1];
		for (int i = 0; i <= (this->vnCnt); ++i) {
			this->grid[i] = new int[this->vtCnt + 1]();
		}

		isCreated = 1;
	}
	~parseGrid() {
		if (isCreated == 1) {
			for (int i = 0; i <= (this->vnCnt); ++i) {
				delete[] this->grid[i];
			}
			delete[] this->grid;
		}
	}
};

vector<word> readWords(const string filePath) {
	vector<word> words;
	fstream file;
	file.open(filePath, ios::in);
	const string iden = "$";
	string line;
	while (getline(file, line)) {
		string::size_type pos = line.find_first_of(iden);
		if (pos != string::npos) {
			words.emplace_back(line.substr(0, pos), line.substr(pos + iden.length()));
		}
	}
	//words.emplace_back("ENDF", "#");
	file.close();
	return words;
}

vector<gram> readGram(const string filePath, string& beginSign) {
	vector<gram> jgram;
	fstream file;
	file.open(filePath, ios::in);
	const string iden = ":= ";
	string line;
	int index = 0;
	while (getline(file, line)) {
		string::size_type pos = line.find_first_of(iden);
		if (pos != string::npos) {
			jgram.emplace_back(line.substr(0, pos));
			string right = line.substr(pos + iden.length());
			string::size_type rpos1 = 0, rpos2 = 0;
			while (rpos1 < right.length()) {
				if (right[rpos1] == '[') {
					rpos2 = right.find_first_of("]", rpos1);
					jgram[index].r.emplace_back(right.substr(rpos1, rpos2 - rpos1 + 1));
				} else if (right[rpos1] == '{') {
					rpos2 = right.find_first_of("}", rpos1);
					jgram[index].r.emplace_back(right.substr(rpos1, rpos2 - rpos1 + 1));
				} else if (right[rpos1] == '$') {
					jgram[index].r.emplace_back("EPS");
					rpos2 = rpos1;
				} else if (right[rpos1] == '#') {
					jgram[index].r.emplace_back("[ENDF]");
					rpos2 = rpos1;
				} else {
					rpos2 = rpos1;
				}
				rpos1 = rpos2 + 1;
			}
			index++;
		} else {
			pos = line.find_first_of("@");
			if (pos != string::npos) {
				beginSign = line.substr(1);
			} else {
				beginSign = "S";
			}
		}
	}
	file.close();
	return jgram;
}

set<string> getVN(vector<gram> &jgram) {
	set<string> vn;
	for (auto& e : jgram) {
		vn.insert(e.l);
	}
	return vn;
}

set<string> getVT(vector<select> &slcts) {
	set<string> vt;
	for (auto& e : slcts) {
		for (auto& e2 : e.SELECT) {
			vt.insert(e2);
		}
	}
	return vt;
}

void outGram(vector<gram> &jgram) {
	cout << "# gram" << endl ;
	int seq = 1;
	for (auto& e : jgram) {
		cout << "(" << seq << ") " << e.l << " -> ";
		for (auto& e2 : e.r) {
			cout << e2;
		}
		seq++;
		cout << endl;
	}
}

bool  extractLGCD(set<string>& vn,vector<gram> &jgram) {
	bool res=false;
	map<string, int> vis;

	for(auto vne:vn){
		vector<int> gcdidx;//存同左部式子序号
		for (int j = 0; j < (int)jgram.size(); ++j) {
			if (jgram[j].l != vne) {//找到同左部式子
				continue;
			}

			gcdidx.push_back(j);
		}

		for(int j=0;j<(int)gcdidx.size();++j){
			vector<int> samidx;

			for(int k=j+1;k<(int)gcdidx.size();++k){
				int tszie = min((int)jgram[gcdidx[j]].r.size(), (int)jgram[gcdidx[k]].r.size());
				int samecnt = 0;

				for (int m = 0; m < tszie; ++m) {
					if (jgram[gcdidx[j]].r[m] == jgram[gcdidx[k]].r[m]) {//查看右部前多少项相同
						samecnt++;
					}else{
						break;
					}
				}

				if (samecnt !=0) {
					samidx.push_back(gcdidx[k]);
				}
			}

			if ((int)samidx.size() != 0) {
				int samecnt=jgram[gcdidx[j]].r.size();
				for(auto e:samidx){
					int tsamecnt=0;
					int tszie = min((int)jgram[gcdidx[j]].r.size(), (int)jgram[e].r.size());
					for (int m = 0; m < tszie; ++m) {
						if (jgram[gcdidx[j]].r[m] == jgram[e].r[m]) {//查看右部前多少项相同
							tsamecnt++;
						}else{
							break;
						}
					}
					samecnt=min(samecnt,tsamecnt);
				}
				samidx.push_back(gcdidx[j]);
				vis[vne]++;

				string vnex = vne;
				for (int k = 1; k <= vis[vne]; ++k) {
					vnex += "+";
				}

				gram tgram(vne);
				tgram.r.assign(jgram[gcdidx[j]].r.begin(), jgram[gcdidx[j]].r.begin() + samecnt);
				tgram.r.push_back("{" + vnex + "}");
				for (int k = 0; k < (int) tgram.r.size(); ++k){
					if(tgram.r[k]=="EPS"){
						tgram.r.erase(tgram.r.begin()+k);
						k--;
					}
				}

				if((int)tgram.r.size()==0){
					tgram.r.push_back("EPS");
				}

				jgram.push_back(tgram);
				res=true;

				//cout<<samecnt<<endl;
				for (auto e : samidx) {
					// cout<<e<<":"<<jgram[e].l<<",";
					// for(auto e2:jgram[e].r){
					// 	cout<<e2;
					// }
					// cout<<endl;
					jgram[e].l = vnex;
					jgram[e].r.erase(jgram[e].r.begin(), jgram[e].r.begin() + samecnt);

					if (jgram[e].r.size() == 0) {
						jgram[e].r.push_back("EPS");
					}
				}
			}
		}

	}
	return res;
}

bool elimateDirectLRecursion(string vn, vector<gram> &jgram) {
	string vnstr = "{" + vn + "}";
	vector<int> lrecur, nlrecur;

	int isHaving = 0;//右部第一个符号是否是自身
	for (int i = 0; i < (int)jgram.size(); ++i) {
		if (jgram[i].l == vn) {
			if (jgram[i].r[0] == vnstr) {
				isHaving = 1;
				lrecur.emplace_back(i);
			} else {
				nlrecur.emplace_back(i);
			}
		}
	}

	if (isHaving == 1) {
		string vnex = vn + "\'";
		string vnexstr = "{" + vnex + "}";
		for (int index : nlrecur) {
			jgram[index].r.emplace_back(vnexstr);
		}
		for (int index : lrecur) {
			jgram[index].l = vnex;
			jgram[index].r.emplace_back(vnexstr);
			jgram[index].r.erase(jgram[index].r.begin());
		}
		int index = jgram.size();
		jgram.emplace_back(vnex);
		jgram[index].r.emplace_back("EPS");
		return true;
	} else {
		return false;
	}
}

void elimateIndirectLRecursion(set<string>& vn, vector<gram> &ojgram) {
	vector<gram> jgram;
	jgram.assign(ojgram.begin(), ojgram.end());

	int isHavingLR = 0;
	set<string>::iterator it1, it2;
	for (it1 = vn.begin(); it1 != vn.end(); ++it1) {//Ai
		string vnistr = "{" + *it1 + "}";

		for (it2 = vn.begin(); it2 != it1; ++it2) { //Aj
			string vnjstr = "{" + *it2 + "}";

			//cout<<*it1<<","<<*it2<<endl;
			for (int i = 0; i < (int)jgram.size(); ++i) {
				if (jgram[i].l == *it1) {//对于左部为Ai的式子
					if (jgram[i].r[0] == vnjstr) {//右部第一个位Aj
						vector<string> tmpr;
						tmpr.assign(jgram[i].r.begin() + 1, jgram[i].r.end());
						jgram[i].r.erase(jgram[i].r.begin());//去掉Ai式子右部开头的Aj
						int isFirstRepl = 1;
						for (int j = 0; j < (int)jgram.size(); ++j) {
							if (jgram[j].l == *it2) {//找到所有Aj的式子
								if (isFirstRepl == 1) {
									jgram[i].r.clear();
									for (string& e : jgram[j].r) {
										if (e == "EPS") {
											continue;
										}
										jgram[i].r.emplace_back(e);
									}
									for (string& e : tmpr) {
										if (e == "EPS") {
											continue;
										}
										jgram[i].r.emplace_back(e);
									}
									if (jgram[i].r.size() == 0) {
										jgram[i].r.emplace_back("EPS");
									}
									isFirstRepl = 0;
								} else {
									int index = jgram.size();
									jgram.emplace_back(*it1);
									for (string& e : jgram[j].r) {
										if (e == "EPS") {
											continue;
										}
										jgram[index].r.emplace_back(e);
									}
									for (string& e : tmpr) {
										if (e == "EPS") {
											continue;
										}
										jgram[index].r.emplace_back(e);
									}
									if (jgram[i].r.size() == 0) {
										jgram[i].r.emplace_back("EPS");
									}
								}
							}
						}
					}
				}
			}
		}

		if (elimateDirectLRecursion(*it1, jgram)) {
			isHavingLR = 1;
		}
	}

	if (isHavingLR == 1) {
		ojgram.assign(jgram.begin(), jgram.end());
	}

	sort(jgram.begin(), jgram.end(), gramCmp);
}

void deleteUnusedFormula(vector<gram> &jgram, string beginSign) {
	for (int i = 0; i < (int)jgram.size(); ++i) {
		if (jgram[i].l == beginSign) {
			continue;
		}

		string vnstr = "{" + jgram[i].l + "}";

		int isHavingVN = 0;

		for (int j = 0; j < (int)jgram.size(); ++j) {
			for (int k = 0; k < (int)jgram[j].r.size(); ++k) { //遍历每一个右部
				if (jgram[j].r[k] == vnstr && jgram[j].l != jgram[i].l) {
					isHavingVN = 1;
					break;
				}
			}
		}

		if (isHavingVN == 0) {
			jgram.erase(jgram.begin() + i);
			i--;
		}
	}
}

map<string, int> getEps(set<string>& vn, vector<gram> &jgram) {
	map<string, int> ded2eps;
	set<string>::iterator it;

	for (it = vn.begin(); it != vn.end(); ++it) {
		ded2eps[*it] = -1;
	}

	vector<gram> tjgram;
	tjgram.assign(jgram.begin(), jgram.end());

	for (int i = 0; i < (int)tjgram.size(); ++i) {//第一次遍历
		if (tjgram[i].r[0] == "EPS") {
			string left = tjgram[i].l;
			ded2eps[left] = 1;
			for (int j = 0; j < (int)tjgram.size(); ++j) {//如果式子右部为空，删除左部符号对应的所有式子
				if (tjgram[j].l == left) {
					tjgram.erase(tjgram.begin() + j);
					j--;
					i = min(i, j);
				}
			}
			continue;
		}

		int isHavingVT = 0;
		for (int j = 0; j < (int)tjgram[i].r.size(); ++j) {
			if (tjgram[i].r[j][0] == '[') {
				isHavingVT = 1;
				break;
			}

		}

		if (isHavingVT == 1) {//如果式子里有终结符号，删掉该式子
			string left = tjgram[i].l;
			tjgram.erase(tjgram.begin() + i);
			i--;

			int isNone = 1;
			for (int j = 0; j < (int)tjgram.size(); ++j) {
				if (tjgram[j].l == left) {
					isNone = 0;
					break;
				}
			}

			if (isNone == 1) {//如果删掉式子后，左部符号再无式子
				ded2eps[left] = 0;
			}
		}
	}

	for (int i = 0; i < (int)tjgram.size(); ++i) {//第二次遍历
		int isNotEPS = 0;
		for (int j = 0; j < (int)tjgram[i].r.size(); ++j) {
			if (tjgram[i].r[j] != "EPS") {
				if (tjgram[i].r[j][0] == '{') {
					string vnsign = tjgram[i].r[j].substr(1, tjgram[i].r[j].length() - 2);

					if (ded2eps[vnsign] == 1) {//右部出现的非终结符可以推导到空，就在该式子里删掉次非终结符
						tjgram[i].r.erase(tjgram[i].r.begin() + j);
						j--;
					} else if (ded2eps[vnsign] == 0) { //如果出现的终结符不能推导到空，删除此式子
						string left = tjgram[i].l;
						tjgram.erase(tjgram.begin() + i);
						i--;
						isNotEPS = 1;
						int isNone = 1;
						for (int j = 0; j < (int)tjgram.size(); ++j) {
							if (tjgram[j].l == left) {
								isNone = 0;
								break;
							}
						}
						if (isNone == 1) {//如果删掉式子后，左部符号再无式子
							ded2eps[left] = 0;
						}
						break;
					}
				}
			} else {
				tjgram[i].r.erase(tjgram[i].r.begin() + j);
				j--;
			}
		}

		if (isNotEPS == 0) {
			if (tjgram[i].r.size() == 0) {//如果在删除后，右部式子为空
				string left = tjgram[i].l;
				ded2eps[left] = 1;
				for (int j = 0; j < (int)tjgram.size(); ++j) {//删掉左部所对应的所有式子
					if (tjgram[j].l == left) {
						tjgram.erase(tjgram.begin() + j);
						j--;
						i = min(i, j);
					}
				}
				continue;
			}
		}
	}
	return ded2eps;
}

void getFIRST(vector<ffset>& ffsets, vector<gram> &jgram, map<string, int> ded2eps) {
	stack<int> idxStack;
	idxStack.push(0);

	while (!idxStack.empty()) {
		int i = idxStack.top();
		if (i >= (int)ffsets.size()) {
			idxStack.pop();
			continue;
		}

		int isUncompleted = 0;
		for (int j = 0; j < (int)jgram.size(); ++j) {
			if (jgram[j].l == ffsets[i].l) {
				if (jgram[j].r[0][0] == '[') {//开头是终结符
					ffsets[i].FIRST.insert(jgram[j].r[0]);
				} else if (jgram[j].r[0] == "EPS") {//开头是空
					ffsets[i].FIRST.insert(jgram[j].r[0]);
				} else if (jgram[j].r[0][0] == '{') {//开头是非终结符
					for (int k = 0; k < (int)jgram[j].r.size(); ++k) {
						string e = jgram[j].r[k];
						if (e[0] == '{') {//式子前几项是非终结符
							string tvn = e.substr(1, e.length() - 2);
							if (ded2eps[tvn] == 1) { //如果这个非终结符可以推导到空
								vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);
								if (lit != ffsets.end()) {
									if (lit->FIRST.size() != 0) {
										set<string>::iterator sit;
										for (sit = lit->FIRST.begin(); sit != lit->FIRST.end(); ++sit) {
											if ((*sit) != "EPS") { //不装空
												ffsets[i].FIRST.insert(*sit);
											}
										}
									} else { //该非终结符的FIRST集合没有完成
										idxStack.push(lit - ffsets.begin());
										isUncompleted = 1;
									}
								}

								if (k == (int)jgram[j].r.size() - 1) { //如果式子全由非终结符组成，且全可以推导至空
									ffsets[i].FIRST.insert("EPS");
								}
							} else if (ded2eps[tvn] == 0) { //如果不能推导到空

								vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);
								if (lit != ffsets.end()) {
									if (lit->FIRST.size() != 0) {
										set<string>::iterator sit;
										for (sit = lit->FIRST.begin(); sit != lit->FIRST.end(); ++sit) { //可以装空
											ffsets[i].FIRST.insert(*sit);
										}
									} else { //该非终结符的FIRST集合没有完成
										idxStack.push(lit - ffsets.begin());
										isUncompleted = 1;
									}
								}
								break;//遇到不能推导至空的非终结符后，不往后看
							}
						} else {//遇到终结符
							ffsets[i].FIRST.insert(e);
							break;
						}
					}
				} else {
					idxStack.pop();
				}
			}
		}
		if (isUncompleted == 0) {
			idxStack.pop();
			idxStack.push(i + 1);
		}
	}
}

void getFOLLOW(vector<ffset>& ffsets, vector<gram> &jgram, map<string, int> ded2eps, string& beginSign) {
	stack<int> idxStack;
	for (int i = (int)ffsets.size() - 1; i >= 0; --i) {
		idxStack.push(i);
	}

	while (!idxStack.empty()) {
		int i = idxStack.top();
		if (i >= (int)ffsets.size()) {
			idxStack.pop();
			continue;
		}

		//cout<<ffsets[i].l<<endl;

		string vnstr = "{" + ffsets[i].l + "}";
		if (ffsets[i].l == beginSign) { //如果是起始非终结符
			ffsets[i].FOLLOW.insert("[ENDF]");//装入#
		}

		int isUncompleted = 0;

		for (int j = 0; j < (int)jgram.size(); ++j) {
			for (int k = 0; k < (int)jgram[j].r.size(); ++k) { //遍历每一个右部
				if (jgram[j].r[k] == vnstr) { //在右部中找到非终结符

					if (k == (int)jgram[j].r.size() - 1) { //如果后面没东西
						string tvn = jgram[j].l;
						vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);

						if (lit != ffsets.end()) {
							if (lit->FOLLOW.size() != 0) {
								set<string>::iterator sit;
								for (sit = lit->FOLLOW.begin(); sit != lit->FOLLOW.end(); ++sit) {
									ffsets[i].FOLLOW.insert(*sit);
								}
							} else { //该非终结符的FOLLOW集合没有完成
								if (tvn != ffsets[i].l) {
									//cout<<lit - ffsets.begin()<<endl;
									//cout << "* " << (lit->l) << endl;
									idxStack.push(lit - ffsets.begin());
									isUncompleted = 1;
								}
							}
						}
					} else {//后面有东西
						while (true) {
							if (k >= (int)jgram[j].r.size() - 1) {
								string tvn = jgram[j].l;
								vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);

								if (lit != ffsets.end()) {
									if (lit->FOLLOW.size() != 0) {
										set<string>::iterator sit;
										for (sit = lit->FOLLOW.begin(); sit != lit->FOLLOW.end(); ++sit) {
											ffsets[i].FOLLOW.insert(*sit);
										}
									} else { //该非终结符的FOLLOW集合没有完成
										if (tvn != ffsets[i].l) {
											idxStack.push(lit - ffsets.begin());
											isUncompleted = 1;
										}
									}
								}
								break;
							}

							if (jgram[j].r[k + 1][0] == '[') { //后面是终结符
								ffsets[i].FOLLOW.insert(jgram[j].r[k + 1]);
								break;
							} else if (jgram[j].r[k + 1][0] == '{') { //后面是非终结符
								string tvn = jgram[j].r[k + 1].substr(1, jgram[j].r[k + 1].length() - 2);
								vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);

								if (lit != ffsets.end()) {
									if (lit->FIRST.size() != 0) {
										set<string>::iterator sit;
										for (sit = lit->FIRST.begin(); sit != lit->FIRST.end(); ++sit) {
											if ((*sit) != "EPS") { //不装空
												ffsets[i].FOLLOW.insert(*sit);
											}
										}
									}
								}

								if (ded2eps[tvn] == 1) { //若非终结符能推导至0
									string tvn = jgram[j].l;
									vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);

									if (lit != ffsets.end()) {
										if (lit->FOLLOW.size() != 0) {
											set<string>::iterator sit;
											for (sit = lit->FOLLOW.begin(); sit != lit->FOLLOW.end(); ++sit) {
												ffsets[i].FOLLOW.insert(*sit);
											}
										} else { //该非终结符的FOLLOW集合没有完成
											if (tvn != ffsets[i].l) {
												idxStack.push(lit - ffsets.begin());
												isUncompleted = 1;
											}
										}
									}
								}
								break;
							} else if (jgram[j].r[k + 1] == "EPS") { //后面是空
								while (jgram[j].r[k + 1] == "EPS") { //找到不是空的下标
									k++;
								}
							} else {
								idxStack.pop();
								idxStack.push(i + 1);
							}
						}
					}

				}
			}
		}

		if (isUncompleted == 0) {
			idxStack.pop();
		}
	}
}

vector<select> getSELECT(vector<ffset>& ffsets, vector<gram> &jgram, map<string, int> ded2eps) {
	vector<select> slcts;
	for (int i = 0; i < (int)jgram.size(); ++i) {
		slcts.emplace_back(jgram[i].l);
		slcts[i].r.assign(jgram[i].r.begin(), jgram[i].r.end());
	}

	for (int i = 0; i < (int)slcts.size(); ++i) {
		int isDed2Eps = 0;
		vector<string> tfirst;
		int isAllEps = 1;

		for (int j = 0; j < (int)slcts[i].r.size(); ++j) {
			if (slcts[i].r[j][0] == '[') { //遇到终止符
				tfirst.emplace_back(slcts[i].r[j]);
				isAllEps = 0;
				break;
			} else if (slcts[i].r[j][0] == '{') { //遇到非终止符
				string tvn = slcts[i].r[j].substr(1, slcts[i].r[j].length() - 2);

				if (ded2eps[tvn] == 0) { //不能推导到空
					isAllEps = 0;

					vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);
					if (lit != ffsets.end()) {
						if (lit->FIRST.size() != 0) {
							set<string>::iterator sit;
							for (sit = lit->FIRST.begin(); sit != lit->FIRST.end(); ++sit) {
								tfirst.emplace_back(*sit);
							}
						}
					}
					break;
				} else if (ded2eps[tvn] == 1) { //能推导到空
					vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), tvn);
					if (lit != ffsets.end()) {
						if (lit->FIRST.size() != 0) {
							set<string>::iterator sit;
							for (sit = lit->FIRST.begin(); sit != lit->FIRST.end(); ++sit) {
								if (*sit != "EPS") {
									tfirst.emplace_back(*sit);
								}
							}
						}
					}
				}
			}
		}

		if (isAllEps == 1) {
			isDed2Eps = 1;
			tfirst.emplace_back("EPS");
		}

		if (isDed2Eps == 0) { //不能推导至空
			for (string& e : tfirst) {
				slcts[i].SELECT.insert(e);
			}
		} else { //能推导至空
			for (string& e : tfirst) {
				if (e != "EPS") {
					slcts[i].SELECT.insert(e);
				}
			}

			vector<ffset>::iterator lit = find(ffsets.begin(), ffsets.end(), slcts[i].l);
			if (lit != ffsets.end()) {
				if (lit->FOLLOW.size() != 0) {
					set<string>::iterator sit;
					for (sit = lit->FOLLOW.begin(); sit != lit->FOLLOW.end(); ++sit) {
						slcts[i].SELECT.insert(*sit);
					}
				}
			}
		}
	}

	return slcts;
}

vector<ffset> getFIRSTAndFOLLOW(set<string>& vn, vector<gram> &jgram, map<string, int>& ded2eps, string& beginSign) {
	vector<ffset> ffsets;
	set<string>::iterator it;

	for (it = vn.begin(); it != vn.end(); ++it) {
		ffsets.emplace_back(*it);
	}

	getFIRST(ffsets, jgram, ded2eps);
	getFOLLOW(ffsets, jgram, ded2eps, beginSign);
	return ffsets;
}

void processParseGrid(parseGrid& jparg, vector<select>& slcts) {
	set<string>::iterator sit;
	int i = 1;

	for (sit = jparg.vns.begin(); sit != jparg.vns.end(); ++sit) { //遍历非终结符
		int fi = 1;

		for (select& se : slcts) { //寻找左部为该非终结符的所有式子
			if (se.l != *sit) {
				fi++;
				continue;
			}

			for (string e : se.SELECT) { //遍历其SELECT里的所有元素
				set<string>::iterator sit2;
				int j = 1;

				for (sit2 = jparg.vts.begin(); sit2 != jparg.vts.end(); ++sit2) {
					if (*sit2 == e.substr(1, e.length() - 2)) { //遍历终结符集，找到和SELECT里的元素相对应的标号
						jparg.grid[i][j] = fi;
						break;
					}

					j++;
				}
			}

			fi++;
		}

		i++;
	}
}

bool judgeLLG(vector<select>& slcts, map<string, int>& ded2eps) {
	int* vis = new int[(int)slcts.size()]();

	for (int i = 0; i < (int)slcts.size(); ++i) {
		if (vis[i] == 0) {
			vis[i] = 1;

			set<string> stint(slcts[i].SELECT);
			int isHavingOther = 0;
			int rDed2EpsCnt = 0;

			for (int j = 0; j < (int)slcts.size(); ++j) {
				if (vis[j] == 0) {
					if (slcts[j].l != slcts[i].l) { //不是同左部的，继续查找
						continue;
					}
					vis[j] = 1;
					isHavingOther = 1;

					set<string> tmpset;
					set_intersection(stint.begin(), stint.end(),
					                 slcts[j].SELECT.begin(), slcts[j].SELECT.end(),
					                 inserter(tmpset, tmpset.begin()));
					stint = set<string>(tmpset);

					for (int k = 0; k < (int)slcts[j].r.size(); ++k) { //判断能不能推导到空
						if (slcts[j].r[k][0] == '[') { //遇到终止符
							break;
						} else if (slcts[j].r[k][0] == '{') { //遇到非终止符
							string tvn = slcts[j].r[k].substr(1, slcts[j].r[k].length() - 2);

							if (ded2eps[tvn] == 0) { //不能推导到空
								break;
							} else if (ded2eps[tvn] == 1) { //能推导到空
								if (k == (int)slcts[j].r.size() - 1) {
									rDed2EpsCnt++;
								} else {
									continue;
								}
							}
						} else if (slcts[j].r[k] == "EPS") {
							if (k == (int)slcts[j].r.size() - 1) {
								rDed2EpsCnt++;
							} else {
								continue;
							}
						}
					}
				}
			}

			if (isHavingOther == 1) {
				if (stint.size() != 0) {
					return false;
				} else {
					if (rDed2EpsCnt > 1) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

bool gridDringLLProcess(parseGrid& jparg, vector<select>& slcts,
                        vector<word>& words, string& beginSign, fstream& outFile) {
	stack<string> par;
	int thrdindx = 0;

	outFile << "# parsing process" << endl;

	par.push("[ENDF]");
	par.push("{" + beginSign + "}");
	words.emplace_back("ENDF", "#");

	int step = 1;
	while (true) {
		outFile << "## step" << step << endl;
		string cur = par.top();
		string curv = cur.substr(1, cur.length() - 2);

		string tthread = "";
		for (int i = thrdindx; i < (int)words.size(); ++i) {
			tthread += words[i].v;
			// if(words[i].v=="{"||words[i].v=="}"||words[i].v=="["||words[i].v=="]"||words[i].v==","){
			// 	tthread+="\n";
			// }
		}
		outFile << "> - top: " << cur << endl;
		outFile << "> - thread:"<<endl;
		outFile<<"> ``` json"<<endl<<"> "<< tthread<<endl<<"> ```" <<endl;

		if (cur[0] == '[' && curv != "ENDF") {
			if (curv == words[thrdindx].k) {
				outFile << "> - match: " << cur << " == [" << words[thrdindx].k << "]" << endl;
				outFile << "> - pop: " << par.top() << endl;
				par.pop();
				thrdindx++;
			} else {
				outFile << "> - error: " << cur << " != [" << words[thrdindx].k << "]" << endl << endl;
				return false;
			}
		} else if (cur[0] == '[' && curv == "ENDF") {
			if (words[thrdindx].k == "ENDF") {
				outFile << "> - match: " << cur << " == [" << words[thrdindx].k << "]" << endl;
				outFile << "> - acc" << endl << endl;
				return true;
			} else {
				outFile << "> - error: " << cur << " != [" << words[thrdindx].k << "]" << endl << endl;
				return false;
			}
		} else {
			int i = 1, j = 1;
			for (string e : jparg.vns) {
				if (e == curv) {
					break;
				}
				i++;
			}
			for (string e : jparg.vts) {
				if (e == words[thrdindx].k) {
					break;
				}
				j++;
			}

			if (jparg.grid[i][j] != 0) {
				outFile << "> - match: " << cur << " -> ";
				for (auto& e : slcts[jparg.grid[i][j] - 1].r) {
					outFile << e <<" ";
				}
				outFile << endl;
				outFile << "> - pop: " << par.top() << endl;
				par.pop();
				int fi = jparg.grid[i][j] - 1;
				for (int i = (int)slcts[fi].r.size() - 1; i >= 0; --i) {
					if (slcts[fi].r[i] != "EPS") {
						par.push(slcts[fi].r[i]);
						outFile << "> - push: " << slcts[fi].r[i] << endl;
					}
				}
			} else {
				outFile << "> - error: no mapping of M(" << cur << ", [" << words[thrdindx].k << "])" << endl << endl;
				return false;
			}
		}
		outFile << endl;
		step++;
	}
	outFile << "> - out of stack" << endl << endl;
	return false;
}

void readIni(const string& , const string& , vector<word>& , vector<gram>& , string& );
void outputInfo(string& , vector<gram>& , set<string>& , map<string, int>& , vector<ffset>& , vector<select>&, fstream&);
void outputPGrid(parseGrid&, vector<select>&, fstream&);
void outputWords(vector<word>&, fstream&);
void convertMD2DOC();

int main() {
	const string wFilePath = "./json_parse/json_words.out";
	const string gFilePath = "./json_parse/json_gram.in";
	const string outFilePath = "./json_parse/parse_res.txt";

	fstream outFile;
	outFile.open(outFilePath, ios::trunc | ios::out);

	vector<word> words;
	vector<gram> jgram;
	string beginSign = "";
	cout<<"# parse json gram? (1 == yes, 0 == no)"<<endl<<">";
	int isParseJSON =1;
	cin>>isParseJSON;
	if(isParseJSON==1){
		readIni(wFilePath, gFilePath, words, jgram, beginSign);//读语法和单词
	}else{
		string newWFilePath="./json_parse/";
		string newGFilePath="./json_parse/";
		string newFileName="";
		cout<<"# input the words file: "<<endl<<">";
		cin>>newFileName;
		newWFilePath+=newFileName;

		cout<<"# input the gram file: "<<endl<<">";
		cin>>newFileName;
		newGFilePath+=newFileName;
		readIni(newWFilePath, newGFilePath, words, jgram, beginSign);
	}


	set<string> vn;
	vn = getVN(jgram);

	sort(jgram.begin(), jgram.end(), gramCmp);
	elimateIndirectLRecursion(vn, jgram);//消除左递归
	vn = getVN(jgram);

	sort(jgram.begin(), jgram.end(), gramCmp);
	while(extractLGCD(vn,jgram)){//提取左公因子
		vn = getVN(jgram);
		jgram.erase(unique(jgram.begin(), jgram.end()),jgram.end());
	}

	deleteUnusedFormula(jgram, beginSign);//消除无用式

	vn = getVN(jgram);//vn集合
	sort(jgram.begin(), jgram.end(), gramCmp);

	map<string, int> ded2eps;
	ded2eps = getEps(vn, jgram);//计算vn能否推导到空


	vector<ffset> ffsets;
	ffsets = getFIRSTAndFOLLOW(vn, jgram, ded2eps, beginSign);//计算FIRST与FOLLOW

	vector<select> slcts;
	slcts = getSELECT(ffsets, jgram, ded2eps);//计算SELECT

	set<string> vt;
	vt = getVT(slcts);//vt集合

	outputInfo(beginSign, jgram, vn, ded2eps, ffsets, slcts, outFile);

	bool isLL = 0;
	isLL = judgeLLG(slcts, ded2eps);//判断是否是LL(1)文法
	outFile << "# is LL(1) gram: " << (isLL ? "true" : "false")<< endl << endl;
	cout << "# is LL(1) gram: " << (isLL ? "true" : "false") << endl << endl;

	isLL = 1;
	if (isLL == 1) {
		parseGrid jparg(vn, vt);
		processParseGrid(jparg, slcts);//计算分析表

		outputPGrid(jparg, slcts, outFile);
		outputWords(words, outFile);

		bool isAcc = 0;
		isAcc = gridDringLLProcess(jparg, slcts, words, beginSign, outFile); //表驱动分析
		outFile << "# is Accepted: " << (isAcc ? "true" : "false")<< endl;
	}

	outFile.close();

	int isExportDocx=0;
	cout<<"# export .md and .docx ? (1 == yes, 0 == no)"<<endl<<">";
	cin>>isExportDocx;
	if(isExportDocx!=0){
		convertMD2DOC();
	}

	return 0;
}

void convertMD2DOC(){
	char* buffer;
	string mainPath="";
	if((buffer = getcwd(NULL,0))==NULL){
		perror("Getcwd Error.");
	}else{
		mainPath=buffer;
	}
	string srcFilePath=mainPath+R"(\json_parse\parse_res.txt)";
	string tmpFilePath=mainPath+R"(\json_parse\parse_res.md)";
	string dstFilePath=mainPath+R"(\json_parse\parse_res.docx)";
	system(("pandoc "+srcFilePath+" -t markdown_strict+fenced_code_blocks+pipe_tables --highlight-style kate"+" -o "+tmpFilePath).c_str());
	system(("pandoc "+tmpFilePath+" --highlight-style kate"+" -o "+dstFilePath).c_str());
}

void readIni(const string& wFilePath, const string& gFilePath, vector<word>& words, vector<gram>& jgram, string& beginSign) {
	words = readWords(wFilePath);
	jgram = readGram(gFilePath, beginSign);
}

void outputInfo(string& beginSign, vector<gram>& jgram,
                set<string>& vn, map<string, int>& ded2eps,
                vector<ffset>& ffsets, vector<select>& slcts, fstream& outFile) {
	outFile << "# gram" << endl << "- start: " << beginSign << endl;
	int seq = 1;
	for (auto& e : jgram) {
		outFile << seq << ". " << e.l << " -> ";
		for (auto& e2 : e.r) {
			outFile << e2 <<" ";
		}
		seq++;
		outFile << endl;
	}

	outFile << endl << "# is Able To Deduce To Empty" << endl;
	map<string, int>::iterator mit;
	for (mit = ded2eps.begin(); mit != ded2eps.end(); ++mit) {
		outFile << "- empty(" << (mit->first) << "): " << ((mit->second) ? "true" : "false") << endl;
	}

	outFile << endl << "# FIRST" << endl;
	for (auto& e : ffsets) {
		outFile << "- FIRST(" << e.l << "): ";
		int index = 0;
		for (auto& e2 : e.FIRST) {
			outFile << e2 << ((index != (int)e.FIRST.size() - 1) ? "," : "");
			index++;
		}
		outFile << endl;
	}

	outFile << endl << "# FOLLOW" << endl;
	for (auto& e : ffsets) {
		outFile << "- FOLLOW(" << e.l << "): ";
		int index = 0;
		for (auto& e2 : e.FOLLOW) {
			outFile << e2 << ((index != (int)e.FOLLOW.size() - 1) ? "," : "");
			index++;
		}
		outFile << endl;
	}

	outFile << endl << "# SELECT" << endl;
	for (auto& e : slcts) {
		outFile << "- SELECT(" << e.l << " -> ";
		for (auto& e2 : e.r) {
			outFile << e2;
		}
		outFile << "): ";
		int index = 0;
		for (auto& e2 : e.SELECT) {
			outFile << e2 << ((index != (int)e.SELECT.size() - 1) ? "," : "");
			index++;
		}
		outFile << endl;
	}
	outFile << endl;
}

void outputPGrid(parseGrid& jparg, vector<select>& slcts, fstream& outFile) {
	int* colw = new int[jparg.vtCnt + 1]();
	//	计算列宽
	auto it = jparg.vts.begin();
	int i = 1;
	while (it != jparg.vts.end()) {
		if (*it == "ENDF") {
			colw[i] = max(colw[i], 1);
		} else {
			colw[i] = max(colw[i], (int)(*it).length());
		}
		it++;
		i++;
	}

	it = jparg.vns.begin();
	i = 1;
	while (it != jparg.vns.end()) {
		colw[0] = max(colw[0], (int)(*it).length());
		for (int j = 1; j <= jparg.vtCnt; ++j) {
			if (jparg.grid[i][j] == 0) {
				colw[j] = max(colw[j], 1); //"null"
				continue;
			}

			int tlen = 3; //"-> "
			for (auto& e : slcts[jparg.grid[i][j] - 1].r) {
				tlen += (int)e.length();
			}
			colw[j] = max(colw[j], tlen);
		}

		it++;
		i++;
	}
	int roww = 0;//计算总列宽
	for (int i = 0; i < (jparg.vtCnt + 1); ++i) {
		roww += colw[i] + 3;
	}
	roww++;
	//输出
	it = jparg.vts.begin();
	outFile << "# grid" << endl;
	// for (int i = 0; i < roww; ++i) {
	// 	outFile << "-";
	// }
	// outFile << endl;
	outFile << "| " << setw(colw[0]) << " ";
	outFile << " | ";
	i = 1;
	while (it != jparg.vts.end()) {//第一行
		if (*it == "ENDF") {
			outFile << right << setw(colw[i]) << "#";
			outFile << " | ";
		} else {
			outFile << right << setw(colw[i]) << *it;
			outFile << " | ";
		}
		it++;
		i++;
	}
	outFile << endl;

	int posidx = 0;
	int tpos = 1;
	for (int j = 1; j <= roww; ++j) {
		if (j == tpos) {
			outFile << "|";
			tpos += colw[posidx++] + 3;
		} else {
			outFile << "-";
		}
	}
	outFile << endl;

	it = jparg.vns.begin();
	i = 1;
	while (it != jparg.vns.end()) {
		// int posidx = 0;
		// int tpos = 1;
		// for (int j = 1; j <= roww; ++j) {
		// 	if (j == tpos) {
		// 		outFile << "|";
		// 		tpos += colw[posidx++] + 3;
		// 	} else {
		// 		outFile << "-";
		// 	}
		// }
		// outFile << endl;

		outFile << "| " << left << setw(colw[0]) << *it;
		outFile << " | ";
		for (int j = 1; j <= jparg.vtCnt; ++j) {
			if (jparg.grid[i][j] == 0) {
				outFile << right << setw(colw[j]) << " ";
				outFile << " | ";
				continue;
			}

			string tfrm = "-> ";
			for (auto& e : slcts[jparg.grid[i][j] - 1].r) {
				tfrm += e;
			}
			outFile << right << setw(colw[j]) << tfrm;
			outFile << " | ";
		}
		outFile << endl;
		it++;
		i++;

	}
	// for (int i = 0; i < roww; ++i) {
	// 	outFile << "-";
	// }
	// outFile << endl << endl;
	outFile<<endl;

	delete[] colw;
}

void outputWords(vector<word>& words, fstream& outFile) {
	outFile << "# input words" << endl;
	int index = 0;
	for (auto& e : words) {
		outFile << "[" << e.k << "]";
		if (index != (int)words.size() - 1) {
			outFile << ",";
		}
		index++;
	}
	outFile << endl << endl;
}