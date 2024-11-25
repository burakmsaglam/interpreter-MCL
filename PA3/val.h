#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;

enum ValType { VINT, VREAL, VSTRING, VCHAR, VBOOL, VERR };

class Value {
    ValType    T;
    bool    Btemp;
    int     Itemp;
    double   Rtemp;
    string    Stemp;
    char     Ctemp;
        
       
public:
    Value() : T(VERR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(int vi) : T(VINT), Btemp(false), Itemp(vi), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(double vr) : T(VREAL), Btemp(false), Itemp(0), Rtemp(vr), Stemp(""), Ctemp(0) {}
    Value(string vs) : T(VSTRING), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(vs), Ctemp(0) { }
    Value(char vs) : T(VCHAR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(vs) { }
    
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
     bool IsString() const { return T == VSTRING; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}
    bool IsInt() const { return T == VINT; }
    bool IsChar() const {return T == VCHAR;}
    
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    string GetString() const { if( IsString() ) return Stemp; throw "RUNTIME ERROR: Value not a string"; }
    
    double GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not an integer"; }
    
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a boolean";}
    
    char GetChar() const {if(IsChar()) return Ctemp; throw "RUNTIME ERROR: Value not a boolean";}
    
    void SetType(ValType type)
    {
        T = type;
    }
    
    void SetInt(int val)
    {
        Itemp = val;
    }
    
    void SetReal(double val)
    {
        Rtemp = val;
    }
    
    void SetString(string val)
    {
        Stemp = val;
    }
    
    void SetBool(bool val)
    {
        Btemp = val;
    }
    
    void SetChar(char val)
    {
        Ctemp = val;
    }
    
    
    // numeric overloaded add this to op
    Value operator+(const Value& op) const
    {
        // real or int
        if(op.GetType() == VREAL && T == VINT) return op.GetReal() + Itemp;
        else if(op.GetType() == VINT && T == VREAL) return op.GetInt() + Rtemp;
        // char or string
        else if(op.GetType() == VCHAR && T == VSTRING) return  Stemp + op.GetChar();
        else if(op.GetType() == VSTRING && T == VCHAR) return  Ctemp + op.GetString();
        // int or char
        else if(op.GetType() == VINT && T == VCHAR) return op.GetInt() + Ctemp;
        else if(op.GetType() == VCHAR && T == VINT) return op.GetChar() + Itemp;
        // double or char
        else if(op.GetType() == VREAL && T == VCHAR) return op.GetReal() + Ctemp;
        else if(op.GetType() == VCHAR && T == VREAL) return op.GetChar() + Rtemp;
        // same type double int string char
        else if(op.GetType() == VREAL && T == VREAL) return op.GetReal() + Rtemp;
        else if(op.GetType() == VINT && T == VINT) return op.GetInt() + Itemp;
        else if(op.GetType() == VSTRING && T == VSTRING) return Stemp + op.GetString();
        else if(op.GetType() == VCHAR && T == VCHAR) return Ctemp + op.GetChar();
        // else error
        else return Value();
    }
    
    // numeric overloaded subtract op from this
    Value operator-(const Value& op) const
    {
        {
            // When other is real
            if (op.GetType() == VREAL)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp - op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp - op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            // When other is int
            else if (op.GetType() == VINT)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp - op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp - op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            else
                return Value(); // returns error
        }
    }
    
    // numeric overloaded multiply this by op
    Value operator*(const Value& op) const
    {
        {
            // When other is real
            if (op.GetType() == VREAL)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp * op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp * op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            // When other is int
            else if (op.GetType() == VINT)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp * op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp * op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            else
                return Value(); // returns error
        }
    }
    
    // numeric overloaded divide this by oper
    Value operator/(const Value& op) const
    {
        {
            // When other is real
            if (op.GetType() == VREAL)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp / op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp / op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            // When other is int
            else if (op.GetType() == VINT)
            {
                // When real return real always.
                if (T == VREAL)
                {
                    return Rtemp / op.GetReal();
                }
                else if (T == VINT)
                {
                    return Itemp / op.GetReal();
                }
                else
                    // VERR type will result in "ERROR" message in output overloading
                    return Value(); // returns error
            }
            else
                return Value(); // returns error;
        }
    }
    
    //numeric overloaded Remainder this by op
    Value operator%(const Value & op) const
    {
        if (T == VINT && op.GetType() == VINT)
        {
            return Itemp % op.GetInt();
        }
        else
            return VERR;
    }
       
    //overloaded equality operator of this with op
    Value operator==(const Value& op) const
    {
        // When int char or char int
        if ((T == VINT && op.GetType() == VCHAR) || (T == VCHAR && op.GetType() == VINT))
        {
            // if int char
            if(T == VINT)
                return Itemp == op.GetChar();
            else // if char int
                return Ctemp == op.GetInt();
        }
        // when int real or real int
        else if ((T == VINT && op.GetType() == VREAL) || (T == VREAL && op.GetType() == VINT))
        {
            // if int real
            if(T == VINT)
                return Itemp == op.GetReal();
            else // else real int
                return Rtemp == op.GetInt();
        }
        // same type
        else if (T == op.GetType())
        {
            switch (T)
            {
                case VSTRING:
                    return Stemp == op.GetString();
                case VCHAR:
                    return Ctemp == op.GetChar();
                case VBOOL:
                    return Btemp == op.GetBool();
                case VINT:
                    return Itemp == op.GetInt();
                case VREAL:
                    return Rtemp == op.GetReal();
                case VERR:
                    return Value();
            }
        }
        
        return Value(); // error if not match
    }
    //overloaded inequality operator of this with op
    Value operator!=(const Value& op) const
    {
        // When int char or char int
        if ((T == VINT && op.GetType() == VCHAR) || (T == VCHAR && op.GetType() == VINT))
        {
            // if int char
            if(T == VINT)
                return Itemp != op.GetChar();
            else // if char int
                return Ctemp != op.GetInt();
        }
        // when int real or real int
        else if ((T == VINT && op.GetType() == VREAL) || (T == VREAL && op.GetType() == VINT))
        {
            // if int real
            if(T == VINT)
                return Itemp != op.GetReal();
            else // else real int
                return Rtemp != op.GetInt();
        }
        // same type
        else if (T == op.GetType())
        {
            switch (T)
            {
                case VSTRING:
                    return Stemp != op.GetString();
                case VCHAR:
                    return Ctemp != op.GetChar();
                case VBOOL:
                    return Btemp != op.GetBool();
                case VINT:
                    return Itemp != op.GetInt();
                case VREAL:
                    return Rtemp != op.GetReal();
                case VERR:
                    return Value();
            }
        }
        
        return Value(); // error if not match
    }
    //overloaded greater than operator of this with op
    Value operator>(const Value& op) const
    {
        {
            // When int char or char int
            if ((T == VINT && op.GetType() == VCHAR) || (T == VCHAR && op.GetType() == VINT))
            {
                // if int char
                if(T == VINT)
                    return Itemp > op.GetChar();
                else // if char int
                    return Ctemp > op.GetInt();
            }
            // when int real or real int
            else if ((T == VINT && op.GetType() == VREAL) || (T == VREAL && op.GetType() == VINT))
            {
                // if int real
                if(T == VINT)
                    return Itemp > op.GetReal();
                else // else real int
                    return Rtemp > op.GetInt();
            }
            // same type
            else if (T == op.GetType())
            {
                switch (T)
                {
                    case VSTRING:
                        return Stemp > op.GetString();
                    case VCHAR:
                        return Ctemp > op.GetChar();
                    case VBOOL:
                        return Btemp > op.GetBool();
                    case VINT:
                        return Itemp > op.GetInt();
                    case VREAL:
                        return Rtemp > op.GetReal();
                    case VERR:
                        return Value();
                }
            }
            
            return Value(); // error if not match
        }
    }
    //overloaded less than operator of this with op
    Value operator<(const Value& op) const
    {
        {
            // When int char or char int
            if ((T == VINT && op.GetType() == VCHAR) || (T == VCHAR && op.GetType() == VINT))
            {
                // if int char
                if(T == VINT)
                    return Itemp < op.GetChar();
                else // if char int
                    return Ctemp < op.GetInt();
            }
            // when int real or real int
            else if ((T == VINT && op.GetType() == VREAL) || (T == VREAL && op.GetType() == VINT))
            {
                // if int real
                if(T == VINT)
                    return Itemp < op.GetReal();
                else // else real int
                    return Rtemp < op.GetInt();
            }
            // same type
            else if (T == op.GetType())
            {
                switch (T)
                {
                    case VSTRING:
                        return Stemp < op.GetString();
                    case VCHAR:
                        return Ctemp < op.GetChar();
                    case VBOOL:
                        return Btemp < op.GetBool();
                    case VINT:
                        return Itemp < op.GetInt();
                    case VREAL:
                        return Rtemp < op.GetReal();
                    case VERR:
                        return Value();
                }
            }
            
            return Value(); // error if not match
        }
    }
    //overloaded logical Anding operator of this with op
    Value operator&&(const Value& op) const
    {
        if (op.GetType() != VBOOL || T != VBOOL)
            return Value(); // returns error
            
        else
            return Value(op.GetBool() && Btemp);
    }
    //overloaded logical Oring operator of this with op
    Value operator||(const Value& op) const
    {
        if (op.GetType() != VBOOL || T != VBOOL)
            return Value(); // returns error
            
        else
            return Value(op.GetBool() || Btemp);
    }
    //overloaded logical Complement operator of this object
    Value operator!(void) const
    {
        Value op =0;
        return op;
    }
    
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.Itemp;
        else if(op.IsBool()) out << (op.GetBool()? "true": "false");
        else if( op.IsChar() ) out << op.Ctemp ;
        else if( op.IsString() ) out << op.Stemp ;
        else if( op.IsReal()) out << fixed << showpoint << setprecision(2) << op.Rtemp;
        else if(op.IsErr()) out << "ERROR";
        return out;
    }
};


#endif
