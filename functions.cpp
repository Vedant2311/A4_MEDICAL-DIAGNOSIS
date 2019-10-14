// Given: network Alarm, vector<int> roots, vector<vector<string>> patient_list, vector<vector<int>> unknowns

void traverseIndex(network& Alarm, int index,vector<vector<string>> patient_list){

	find_cpt(Alarm,index);

}

void traverse(network& Alarm, vector<int> roots, vector<vector<string>> patient_list){

	vector<int> newChild;

	for (int i=0; i<roots.size() ; i++){
		traverseIndex(Alarm,roots(i),patient_list);
		vector<int> added = Alarm.get_nth_node(roots(i)).Children;
		newChild.insert(newChild.end(),added.begin, added.end());
	}

	if (newChild.size() ==0) return;
	else{
		traverse(Alarm,newChild,patient_list);
	}


}
