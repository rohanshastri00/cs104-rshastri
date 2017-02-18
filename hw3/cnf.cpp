#include "cnf.h"
using namespace std;

/**
 * Helper function to take the absolute value of an integer
 */
int intabs(int a)
{
    if(a < 0) return -a;
    return a;
}


Clause::Clause() : isTrue_(false)
{
}

Clause::Clause(const vector<int>& vars)
    : vars_(vars), isTrue_(false)
{

}


int Clause::eval(std::map<int,int>& varValues)
{
    
    int trueClauses = 0;

    for (unsigned int i = 0; i < vars_.size(); i++)
    {
        map<int, int>::iterator map_it = varValues.find(intabs(vars_[i]));

        //if value in map is equal to 1 and there is an not exclamation point
        //+1
        if (map_it->second == 1 && vars_[i] > VAL0)
        {
            trueClauses++;
            break;
        }
        //if value in map equal to 0 and exclamation point
        //-1
        if (map_it->second == 0 && vars_[i] < VAL0)
        {
            trueClauses++;
            break;
        }

    }
    //if everything was false before and now is not
    if (!isTrue_ && trueClauses != 0)
    {
        isTrue_ = true;
        return 1;

    }

    //if everything was false and everything still is
    else if (isTrue_ && trueClauses == 0)
    {
        isTrue_ = false;
        return -1;
    }

    else 
    {
        return 0;
    }

}


CNFFormula::CNFFormula(int nVars, const vector<Clause*>& clauses)
    : clauses_(clauses), numSatisfied_(0)
{


    //assign all values to unassigned

    for (int i = 1; i <= nVars; i++)
    {
        varValues_.insert(make_pair(i, UNK));
    }
    set<Clause*> tempSetClauses;
    for (int i = 1; i <= nVars; i++)
    {
        //iterate through clauses
        for (unsigned int j = 0; j < clauses.size();j++)
        {
            //each clauses has a priv member vector called vars
            for (unsigned int k = 0; k < clauses[j]->vars().size();k++)
            {
                if (i == intabs(clauses[j]->vars()[k]))
                {
                    tempSetClauses.insert(clauses[j]); 
                    break;
                }
            }
        }
        varToClauses_.insert(make_pair(i, tempSetClauses));
        tempSetClauses.clear();   
    }
}

CNFFormula::~CNFFormula()
{
   
    for (unsigned int i = 0; i < clauses_.size();i++)
    {
        //loop through vector of clauses
        delete clauses_[i];
    }
}

bool CNFFormula::isSatisfied() const
{
    return numSatisfied_ == clauses_.size();
}

void CNFFormula::printVarValues() const
{

    map<int, int>::const_iterator map_it;
    for (map_it = varValues_.begin(); map_it != varValues_.end(); map_it++)
    {
     
        cout << "Var " << map_it->first << " : ";
        if (map_it->second == -1)
        {
            cout << "Unassigned" << endl;
           
        }
        else 
        {
            cout << map_it->second << endl;
        }
    }

}


void CNFFormula::assignVar(int var, int val)
{

    map<int, int>::iterator map_it;
    map_it = varValues_.find(var);

    if (map_it != varValues_.end())

    {
        map_it->second = val;
    }

    set<Clause*>::iterator set_it = varToClauses_.find(var)->second.begin();

    if (varToClauses_.find(var)->second.size() != 0)
    {
        for (set_it = varToClauses_.find(var)->second.begin(); 
            set_it != varToClauses_.find(var)->second.end(); set_it++)
        {   
 
           numSatisfied_ += (*set_it)->eval(varValues_);

        }
    }

}

