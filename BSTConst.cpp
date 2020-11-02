//ALL ABOUT BINARY SEARCH TREES
#include<iostream>
#include<vector>
#include<algorithm>
#include<cfloat>
using namespace std;

class BST{
public:
	int value;
	BST *left;
	BST *right;

	BST(int val){
		value=val;
		left=NULL;
		right=NULL;
	}

//DISPLAY THE CONTENTS OF THE TREE
	void display(){
		BST *currentNode=this;
		if(currentNode==NULL)
			return;
		currentNode->left->display();
		cout<<currentNode->value;
		currentNode->right->display();
	}

//INSERT VALUES IN THE BST
	BST &insert(int val){
		BST *currentNode=this;
		while(true){
			if(val<currentNode->value){
				if(currentNode->left==NULL){
					BST *newNode=new BST(val);
					currentNode->left=newNode;
					break;
				}
				else
					currentNode=currentNode->left;
			}
			else{
				if(currentNode->right==NULL){
					BST *newNode=new BST(val);
					currentNode->right=newNode;
					break;
				}
				else
					currentNode=currentNode->right;
			}
		}
		return *this;
	}

//CHECK IF THE BST CONTAINS A CERTAIN VALUE
    bool contains(int val){
    	BST *currentNode=this;
    	while(currentNode!=NULL){
    		if(val<currentNode->value)
    			currentNode=currentNode->left;
    		else if(val>currentNode->value)
    			currentNode=currentNode->right;
    		else
    			return true;
    	}
    	return false;
    }

//DELETE A NODE FROM THE BST
    BST &remove(int val,BST *parentNode=NULL){
    	BST *currentNode=this;
    	while(currentNode!=NULL){
    		if(val<currentNode->value){
    			parentNode=currentNode;
    			currentNode=currentNode->left;
    		}
    		else if(val>currentNode->value){
    			parentNode=currentNode;
    			currentNode=currentNode->right;
    		}
    		else{
    			if(currentNode->left!=NULL && currentNode->right!=NULL){
    				currentNode->value=currentNode->right->getMinValue();
    				currentNode->right->remove(currentNode->value,currentNode);
    			}
    			else if(parentNode=NULL){
    				if(currentNode->left!=NULL){
    					currentNode->value=currentNode->left->value;
    					currentNode->right=currentNode->left->right;
    					currentNode->left=currentNode->left->left;
    				}
    				else if(currentNode->right!=NULL){
    					currentNode->value=currentNode->right->value;
    					currentNode->left=currentNode->right->left;
    					currentNode->right=currentNode->right->right;
    				}
    				else{
    					//single node tree. do nothing.
    				}
    			}
    		    else if(parentNode->left==currentNode){
    		    	parentNode->left=currentNode->left!=NULL? currentNode->left:currentNode->right;
    		    }
    		    else if(parentNode->right==currentNode){
    		    	parentNode->right=currentNode->left!=NULL?currentNode->left:currentNode->right;
    		    }
    		    break;
    		}
    	}
    	return *this;
    }

    int getMinValue(){
    	if(left==NULL)
    		return value;
    	else
    		return left->getMinValue();
    }

 //INORDER TRAVERSAL
    vector<int> inOrderTraverse(BST *tree,vector<int> array){
    	if(tree->left!=NULL)
    		array=inOrderTraverse(tree->left,array);
    	array.push_back(tree->value);
    	if(tree->right!=NULL)
    		array=inOrderTraverse(tree->right,array);

    	return array;
    }

//PREORDER TRAVERSAL
    vector<int> preOrderTraverse(BST *tree,vector<int> array){
    	array.push_back(tree->value);
    	if(tree->left!=NULL)
    		array=preOrderTraverse(tree->left,array);
    	if(tree->right!=NULL)
    		array=preOrderTraverse(tree->right,array);

    	return array;
    }

//POSTORDER TRAVERSAL
    vector<int> postOrderTraverse(BST *tree,vector<int> array){
    	if(tree->left!=NULL)
    		array=postOrderTraverse(tree->left,array);
    	if(tree->right!=NULL)
    		array=postOrderTraverse(tree->right,array);
    	array.push_back(tree->value);

    	return array;
    }

//VALIDATE BST-CHECK WEATHER THE DATA STRUCTURE IS A BST OR NOT
    bool validateBST(BST *tree){
    	return validateBSTHelper(tree,INT_MIN,INT_MAX);
    }

    bool validateBSTHelper(BST *tree,int minValue,int maxValue){
    	if(tree->value<minValue || tree->value>=maxValue)
    		return false;
    	if(tree->left!=NULL && !validateBSTHelper(tree->left,minValue,tree->value))
    		return false;
        if(tree->right!=NULL && !validateBSTHelper(tree->right,tree->value,maxValue))
        	return false;

        return true;
    }

//FIND CLOSEST VALUE IN A BST
    int findClosestValueBST(BST *tree,int target){
    	return findClosestValueBSTHelper(tree,target,INT_MAX);
    }

    int findClosestValueBSTHelper(BST *tree,int target,int closest){
    	if(abs(target-closest)>abs(target-tree->value)){
    		closest=tree->value;
    	}
    	
    	if(target<tree->value && tree->left!=NULL)
    		return findClosestValueBSTHelper(tree->left,target,closest);
        else if(target>tree->value && tree->right!=NULL)
        	return findClosestValueBSTHelper(tree->right,target,closest);
        else
        	return closest;
    }

//BRANCH SUMS
    vector<int> branchSums(BST *tree){
    	vector<int> sums;
    	calculateBranchSums(tree,0,sums);
    	return sums;
    }
    void calculateBranchSums(BST *tree,int runningSum,vector<int> sums){
    	if(tree==NULL)
    		return;
    	int newRunningSum=newRunningSum+tree->value;
    	if(tree->left==NULL && tree->right==NULL){
    		sums.push_back(newRunningSum);
    		return;
    	}
    	calculateBranchSums(tree->left,newRunningSum,sums);
    	calculateBranchSums(tree->right,newRunningSum,sums);
    }
};

int main(){
	cout<<"hi"<<" ";
	BST *obj=new BST(10);
	obj->insert(5);
	obj->insert(3);
	obj->insert(12);
	obj->insert(1);
	obj->insert(15);

    obj->display();
    if(obj->contains(5))
      cout<<"yes"<<" ";

    vector<int> pre;
    pre=obj->inOrderTraverse(obj,pre);
    cout<<pre.size();
    for(int i=0;i<pre.size();i++)
    	cout<<pre.at(i)<<" ";
    cout<<endl;

    cout<<"closest value"<<obj->findClosestValueBST(obj,13)<<" ";

    bool x=obj->validateBST(obj);
    cout<<x<<" ";
    /*obj->remove(3,obj);
    if(obj->contains(3))
    	cout<<"deletion unsuccessful"<<" ";
    else
    	cout<<"successful"<<" ";*/

    return 0;
}