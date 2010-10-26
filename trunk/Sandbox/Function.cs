﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sandbox
{
    public class Function
    {
        static long Factorial(long number)
        {
            if (number <= 1)
                return 1;
            else
                return number * Factorial(number - 1);
        }

        // Just had an idea to have predefined constants - want to write it down
        // If we can use a flag character (I was thinking #) before a predefined keyword
        // we can parse that out. Ex. #pir^2 -> 3.14159r^2
        #region Variable Members

        #region Private
        #region Vars, Structs, etc.
        private string definition;
        private char parameter;

        private double argval; // placeholder for the value passed to the function

        Arg_Type Arg_Type_Of(char c)
        {
            const string _operators = "+-*/^%!";
            const string _lgroupers = "([{";
            const string _rgroupers = ")]}";

            if (Char.IsDigit(c) || c == '.')
                return Arg_Type.Constant;
            if (c == this.Parameter)
                return Arg_Type.Variable;
            if (_operators.Contains(c))
                return Arg_Type.Operator;
            if (_lgroupers.Contains(c))
                return Arg_Type.LGrouper;
            if (_rgroupers.Contains(c))
                return Arg_Type.RGrouper;
            if (c == '#')
                return Arg_Type.Predefined;
            return Arg_Type.Unknown;
        }
        public class Arg_Part
        {
            /// <summary>
            /// The string value of the struct.
            /// </summary>
            public string value;
            /// <summary>
            /// Constant, Variable, Grouper, etc.
            /// </summary>
            public Arg_Type classification;
            public Operators opType;
            public Arg_Part(string Value, Arg_Type Classification)
            {
                value = Value;
                classification = Classification;
                opType = Operators.NULL;
                if (classification == Arg_Type.Operator) {
                    switch (value) {
                        case "+": opType = Operators.ADD; break;
                        case "-": opType = Operators.SUBTRACT; break;
                        case "*": opType = Operators.MULTIPLY; break;
                        case "/": opType = Operators.DIVIDE; break;
                        case "%": opType = Operators.MODULO; break;
                        case "^": opType = Operators.EXPONENT; break;
                        case "!": opType = Operators.FACTORIAL; break; } }
            }
            public Arg_Part()
            {
                value = string.Empty;
                classification = Arg_Type.Void;
                opType = Operators.NULL;
            }
            public static Arg_Part operator +(Arg_Part a, Arg_Part b)
            {
                Arg_Part r = new Arg_Part();
                if (a.classification == b.classification)
                {
                    r.value = a.value + b.value;
                    r.classification = a.classification;
                }
                else
                    throw new ArgumentException("Operands need to be of the same classification");

                return r;
            }
        };
        // I believe the ICollection is the closest thing to a C# vector
        public List<Arg_Part> arg_list = new List<Arg_Part> { };
#endregion
        #region Tokenize
        private void Validate()
        {
            this.Definition = this.Definition.Replace(" ", ""); // Keep this in case I remember anything else we should strip
            //this.Definition = this.Definition.Replace("#pi", Math.PI.ToString());
        }
        private List<Arg_Part> Tokenize_20101018(string s)
        {
            Validate();

            // create and prime a List with the first char's Arg_Part representation
            List<Arg_Part> r = new List<Arg_Part>() { new Arg_Part(s[0].ToString(), Arg_Type_Of(s[0])) };

            for (int index = 1; index < s.Length; index++)
            {
                Arg_Part This = new Arg_Part(s[index].ToString(), Arg_Type_Of(s[index]));

                try
                {
                    // try appending the value of this char's Arg_Part representation
                    r[r.Count - 1] += This;
                }
                catch (ArgumentException)
                {
                    // if the classifications are incompatible, add it as a new Arg_Part
                    r.Add(This);
                }
            }

            return r;
        }
        private void Tokenize()//Tokenize_StevensTest
        {
            // Strip whitespace and check for invalid 
            Validate();

            bool isVariable = false; // To check if we should keep adding to the variable string

            for (int index = 0; index < this.definition.Length; index++)
            {
                char c = definition[index];
                Arg_Type type = Arg_Type_Of(c);

                // This is the predefined constants parser... its completion level is like -45684%

                //if (type == Arg_Types.Predefined)
                //{
                //    int start = index++;
                //    for (; index < this.definition.Length; index++)
                //    {
                //        if (!Char.IsLetter(this.definition[index]))
                //        {
                //            arg_list.Add(new Arg_Part(this.definition.Substring(start, index - start), Arg_Types.Predefined));
                //            break;
                //        }
                //    }
                //}

                // If its a variable then lets see if we had a variable last time we went through
                if (type == Arg_Type.Constant)
                {
                    if (isVariable)
                    { // Append to the last argument in the list, our variable
                        Arg_Part buf = arg_list[arg_list.Count-1]; 

                        buf.value += c;
                        arg_list[arg_list.Count-1] = buf;
                    }   
                    else
                    { // It's a new variable, let's make a new argument and add it to the list
                        isVariable = true;

                        Arg_Part buf = new Arg_Part(c.ToString(), type);
                       
                        arg_list.Add(buf);
                    }
                }
                else
                {
                    isVariable = false;

                    Arg_Part buf = new Arg_Part(c.ToString(), type);
                    Arg_Part prevArg = arg_list[arg_list.Count - 1];

                    if (prevArg.classification == Arg_Type.Operator && type == Arg_Type.Operator)
                        throw new InvalidOperationException("Two or more operators were found adjacent to each another: not allowed! PARADOX!");

                    arg_list.Add(buf);
                }
            }
        }

        private void __Tokenize_old()
        {
            string arg_buffer = "";
            Arg_Type type_buffer = Arg_Type.Void;
            foreach (char c in this.Definition)
            {
                if (type_buffer == Arg_Type.Void)
                {
                    type_buffer = Arg_Type_Of(c);
                    arg_buffer += c;
                    continue;
                }
                if (type_buffer == Arg_Type_Of(c))
                    arg_buffer += c;

                if ((type_buffer != Arg_Type_Of(c)) || (this.Definition[this.Definition.Length - 1] == c))
                {
                    Arg_Part buf = new Arg_Part(arg_buffer, type_buffer);

                    if (buf.classification == Arg_Type.Operator && buf.value.Length > 1)
                        throw new InvalidOperationException("Two or more operators were found adjacent to each another: not allowed!");

                    arg_list.Add(buf);
                    arg_buffer = c.ToString();
                    type_buffer = Arg_Type_Of(c);
                }
            }
        }
        #endregion
        #region Do Work, Son!

        /// <summary>
        /// Status: Complete
        /// Insert implied operators in the arg_list so that 2x becomes 2*x
        /// </summary>
        /// <param name="ops">The collection of Arg_Parts to perform the operation on. This may become obselete as we optimize.</param>
        private void ParseImpliedMultiplication(ref List<Arg_Part> ops)
        {
            for (int index = 0; index < ops.Count-1; index++)
            {
                // if ConstantVariable OR VariableConstant OR etc
                // may want to revise so that VariableConstant is parsed as Variable^Constant
                if (((ops[index].classification == Arg_Type.Constant) && (ops[index + 1].classification == Arg_Type.Variable)) ||
                    ((ops[index].classification == Arg_Type.Variable) && (ops[index + 1].classification == Arg_Type.Constant)) ||
                    ((ops[index].classification == Arg_Type.Constant) && (ops[index + 1].classification == Arg_Type.LGrouper)) ||
                    ((ops[index].classification == Arg_Type.Variable) && (ops[index + 1].classification == Arg_Type.LGrouper)))
                    ops.Insert(index + 1, new Arg_Part("*", Arg_Type.Operator));
            }
        }

        /// <summary> Status: Complete
        /// An archetype to perform a binary operation (5+4, 8*46, etc)
        /// </summary>
        /// <param name="one">The first operand</param>
        /// <param name="op">The operator</param>
        /// <param name="two">The second operand</param>
        /// <remarks>
        /// Binary Operator Parser Algorithm (+, -, *, /, ^, more?)
        /// SWITCH CONTINUE(TRUE)
        /// 
        /// While CONTINUE
        /// {
        /// 	While iterating through the characters in a string
        /// 		if this is the last character
        /// 			Stop
        /// 		if this character is an operator (this should never be the last character per the Function::Validate() function; to be written)
        /// 			iterate left until a non-digit is found
        /// 			store index of last digit found [LINDEX]
        /// 			convert the substring from ([LINDEX] up to but not including the operator [INDEX-1]) to a double [LARGUMENT]
        /// 			iterate right until a non-digit is found
        /// 			store index of last digit found [RINDEX]
        /// 			convert the substring from ([RINDEX] up to but not including the operator [INDEX+1]) to a double [RARGUMENT]
        /// 			perform desired operation on [LARGUMENT] and [RARGUMENT] and convert the result to a string
        /// 			remove the substring from [LINDEX] to [RINDEX] and replace it with the resulted string [at INDEX]
        /// }
        /// </remarks>
        private Arg_Part DoBinary(Arg_Part one, Operators op, Arg_Part two)
        {
            if (op == Operators.FACTORIAL)
                throw new ArgumentException("The FACTORIAL operator is unary; please provide a binary operator.");
            switch (op)
            {
                case Operators.ADD:
                    return new Arg_Part((Double.Parse(one.value) + Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                case Operators.SUBTRACT:
                    return new Arg_Part((Double.Parse(one.value) - Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                case Operators.MULTIPLY:
                    return new Arg_Part((Double.Parse(one.value) * Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                case Operators.DIVIDE:
                    return new Arg_Part((Double.Parse(one.value) / Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                case Operators.MODULO:
                    return new Arg_Part((Double.Parse(one.value) % Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                case Operators.EXPONENT:
                    return new Arg_Part(Math.Pow(Double.Parse(one.value), Double.Parse(two.value)).ToString(), Arg_Type.Constant);
                default:
                    return new Arg_Part();
            }
        }

        /// <summary>
        /// An archetype to perform a unary operation (5!, etc)
        /// </summary>
        /// <param name="arg">The operand</param>
        /// <param name="op">The operater</param>
        private Arg_Part DoUnary(Arg_Part arg, Operators op)
        {
            if (op != Operators.FACTORIAL)
                throw new ArgumentException("Please provide an unary operator.");
            if (op == Operators.FACTORIAL && (int)Double.Parse(arg.value) != Double.Parse(arg.value))
                throw new ArgumentException("Factorial requires an integer!");
            return new Arg_Part((Factorial((long)Double.Parse(arg.value))).ToString(), Arg_Type.Constant);
        }

        /// <summary>
        /// Sorts out all of our constant operations, if any
        /// </summary>
        /// <param name="ops"></param>
        private List<Arg_Part> DoConstants(List<Arg_Part> ops)
        {
            ops = this.DoParen(ops);
            ops = this._Exponentiate(ops);
            ops = this._MultiplyAndDivide(ops);
            ops = this._AddAndSubtract(ops);
            return ops;
        }

        private List<Arg_Part> _Exponentiate(List<Arg_Part> ops)
        {
            int count = ops.Count;

            while (true)
            {
                for (int index = 1; index < ops.Count; index++)
                {
                    if (ops[index].classification == Arg_Type.Operator && ops[index].opType == Operators.EXPONENT)
                    {
                        ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.EXPONENT, ops[index + 1]));
                        ops.RemoveRange(index, 3);
                        break;
                    }
                }

                if (ops.Count == count) return ops;
                count = ops.Count;
            }
        }
        private List<Arg_Part> _AddAndSubtract(List<Arg_Part> ops)
        {
            int count = ops.Count;

            while (true)
            {
                for (int index = 1; index < ops.Count; index++)
                {
                    if (ops[index].classification == Arg_Type.Operator)
                    {
                        switch (ops[index].opType)
                        {
                            case Operators.ADD:
                                ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.ADD, ops[index + 1]));
                                ops.RemoveRange(index, 3);
                                break;
                            case Operators.SUBTRACT:
                                ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.SUBTRACT, ops[index + 1]));
                                ops.RemoveRange(index, 3);
                                break;
                        }
                    }
                }

                if (ops.Count == count) return ops;
                count = ops.Count;
            }
        }
        private List<Arg_Part> _MultiplyAndDivide(List<Arg_Part> ops)
        {
            int count = ops.Count;

            while (true)
            {
                for (int index = 1; index < ops.Count; index++)
                {
                    if (ops[index].classification == Arg_Type.Operator)
                    {
                        switch (ops[index].opType)
                        {
                            case Operators.MULTIPLY:
                                ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.MULTIPLY, ops[index + 1]));
                                ops.RemoveRange(index, 3);
                                break;
                            case Operators.DIVIDE:
                                ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.DIVIDE, ops[index + 1]));
                                ops.RemoveRange(index, 3);
                                break;
                            case Operators.MODULO:
                                ops.Insert(index - 1, DoBinary(ops[index - 1], Operators.MODULO, ops[index + 1]));
                                ops.RemoveRange(index, 3);
                                break;
                            case Operators.FACTORIAL:
                                ops.Insert(index - 1, DoUnary(ops[index - 1], Operators.FACTORIAL));
                                ops.RemoveRange(index, 2);
                                break;
                        }
                    }
                }

                if (ops.Count == count) return ops;
                count = ops.Count;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="ops"></param>
        private List<Arg_Part> DoParen(List<Arg_Part> ops)
        {
              for(int index = 0; index < ops.Count; index++)
              {
                    if(ops[index].classification == Arg_Type.LGrouper)
                    {
                          switch(ops[index].value)
                          {
                                case "(":
                                    int index2 = FindBrother(ops, index);
                                    // need to have a private Constructor for Function that takes a List of Arg_Parts
                                    Function inner = new Function(ops.GetRange(index+1, index2 - index-1), this.parameter);
                                    double total_val = inner.Evaluate(this.argval);
                                    Arg_Part innerVal = new Arg_Part(inner.arg_list[0].value, Arg_Type.Constant);
                                    int x = 0;
                                    ops.RemoveRange(index, index2 - index + 1);
                                    ops.Insert(index, innerVal);
                                        break;
                                case "[":
                                    // '' likewise ''
                                        break;
                                case "{":
                                    // '' likewise ''
                                        break;
                          }
                    }
              }
              return ops;
        }

        private int FindBrother(List<Arg_Part> ops, int i)
        {
            LGroupers Class = (LGroupers)ops[i].value[0];
            RGroupers AntiClass;
            switch (Class)
            {
                case LGroupers.BRACE:
                    AntiClass = RGroupers.BRACE;
                    break;
                case LGroupers.BRACKET:
                    AntiClass = RGroupers.BRACKET;
                    break;
                case LGroupers.PAREN:
                    AntiClass = RGroupers.PAREN;
                    break;
            }
            int balance = 0;
            int index = i;
            for (; index < ops.Count; index++)
            {
                if (ops[index].classification == Arg_Type.LGrouper)
                {    
                    balance++;
                }
                if (ops[index].classification == Arg_Type.RGrouper)
                {    
                    balance--;
                }
                if (balance == 0)
                {
                    Console.WriteLine(index);
                    return index;
                }
            }
            return index;
        }

        #endregion
        #endregion

        #region Public

        public string Definition
        {
            get { return definition; }
            set { definition = value; }
        }

        public char Parameter
        {
            get { return parameter; }
            //set { parameter = value; }
        }

        public double Evaluate(double argument)
        {
            double value = Double.NaN;

            return value;
        }

        #endregion

        #endregion

        #region Constructors

        /// <summary>
        /// Function Constructor
        /// </summary>
        /// <param name="Def">The function, i.e. f(t)</param>
        /// <param name="Param">The variable of the function, i.e. 't'</param>
        public Function(string Def, char Param)
        {
            this.definition = Def;
            this.parameter = Param;

            this.arg_list = Tokenize_20101018(this.definition);

            this.ParseImpliedMultiplication(ref this.arg_list);

            this.arg_list = DoConstants(arg_list);
            // Sort out our constant operations, if any
            //int before = 0, after = 0;
            //do {
            //    before = arg_list.Count;
            //    this.DoConstants(ref arg_list);
            //    after = arg_list.Count;
            //} while (before != after);
        }
        private Function(List<Arg_Part> ops, char param)
        {
            this.arg_list = DoConstants(ops);
            this.ParseImpliedMultiplication(ref this.arg_list);
            this.parameter = param;
        }
        #endregion

        #region Groupers
        public enum Arg_Type
        {
            Constant,
            Predefined,
            Variable,
            Operator,
            LGrouper,
            RGrouper,
            Unknown,
            Void
        }
        public enum Operators
        {
            ADD = '+',
            SUBTRACT = '-',
            MULTIPLY = '*',
            DIVIDE = '/',
            EXPONENT = '^',
            MODULO = '%',
            FACTORIAL = '!',
            NULL
        }
        public enum LGroupers
        {
            PAREN = '(',
            BRACKET = '[',
            BRACE = '{',
        }
        public enum RGroupers
        {
            PAREN = ')',
            BRACKET = ']',
            BRACE = '}'
        }
        #endregion
    }
}