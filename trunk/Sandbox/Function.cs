using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// two groupers in a row

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
        // If we can use a flag character (I was thinking # or @) before a predefined keyword
        // we can parse that out. Ex. #pir^2 -> 3.14159r^2
        #region Variable Members

        #region Private
        #region Vars, Structs, etc.

        private string definition;
        private char parameter;

        private double argval; // placeholder for the value passed to the function

        /// <summary>
        /// Converts a char into an Arg_Type
        /// </summary>
        /// <param name="c">The char to classify</param>
        /// <returns>The classification of c</returns>
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
        /// <summary>
        /// A monument to all your sins.
        /// </summary>
        public class Arg_Part
        {
            #region Instance Variables
            /// <summary>
            /// The string value of the struct.
            /// </summary>
            public string value;
            /// <summary>
            /// Constant, Variable, Grouper, etc.
            /// </summary>
            public Arg_Type classification;
            /// <summary>
            /// The operator (iff it is Arg_Type.Operator)
            /// </summary>
            public Operators opType;
            #endregion

            /// <summary>
            /// Recommended constructor for an Arg_Part
            /// </summary>
            /// <param name="Value">The string value of the Arg_Part</param>
            /// <param name="Classification">its Arg_Type</param>
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

            /// <summary>
            /// Default constructor for an empty Arg_Part
            /// </summary>
            public Arg_Part()
            {
                value = string.Empty;
                classification = Arg_Type.Void;
                opType = Operators.NULL;
            }

            /// <summary>
            /// Concactenates the values of two Arg_Parts
            /// </summary>
            /// <param name="a">first arg</param>
            /// <param name="b">second arg</param>
            /// <returns>a new Arg_Part with the same classification as (a,b) but with both values.</returns>
            /// <remarks>essentially the same as string+string</remarks>
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

        /// <summary>
        /// The master list... muhahahaha
        /// </summary>
        public List<Arg_Part> arg_list = new List<Arg_Part> { };
#endregion
        #region Tokenize
        private void Validate()
        {
            this.Definition = this.Definition.Replace(" ", ""); // Keep this in case I remember anything else we should strip
            //this.Definition = this.Definition.Replace("#pi", Math.PI.ToString());
        }
        private List<Arg_Part> Tokenize(string s)
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
                    if (This.classification == Arg_Type.RGrouper || This.classification == Arg_Type.LGrouper)
                    {
                        //throw new ArgumentException("This was just to force the compiler to create a new token; nothing is wrong. Well, if the program has crashed there is definitely something wrong, but I swear, it's not my fault.");
                    }
                }
                catch (ArgumentException)
                {
                    // if the classifications are incompatible, add it as a new Arg_Part
                    r.Add(This);
                }
            }

            return r;
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
        /// <param name="ops">The list of Arg_Parts to do such on</param>
        private List<Arg_Part> DoConstants(List<Arg_Part> ops)
        {
            ops = this.DoParen(ops);
            ops = this._Exponentiate(ops);
            ops = this._MultiplyAndDivide(ops);
            ops = this._AddAndSubtract(ops);
            return ops;
        }

        /// <summary>
        /// Performs Exponentiation
        /// </summary>
        /// <param name="ops">The list of Arg_Parts to do such on</param>
        /// <returns>The modified list of Arg_Parts</returns>
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
        /// <summary>
        /// Performs Addition and Subtraction
        /// </summary>
        /// <param name="ops">The list of Arg_Parts to do such on</param>
        /// <returns>The modified list of Arg_Parts</returns>
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
        /// <summary>
        /// Performs Multiplication (and Factorials) and Division and (Modulos)
        /// </summary>
        /// <param name="ops">The list of Arg_Parts to do such on</param>
        /// <returns>The modified list of Arg_Parts</returns>
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
        /// Handles parentheticals recursively
        /// </summary>
        /// <param name="ops">The list of Arg_Parts to do such on</param>
        /// <returns>The modified list of Arg_Parts</returns>
        private List<Arg_Part> DoParen(List<Arg_Part> ops)
        {
              for(int index = 0; index < ops.Count; index++)
              {
                    if(ops[index].classification == Arg_Type.LGrouper)
                    {
                        // Get the index of the closing Grouper
                        int index2 = FindBrother(ops, index);
                        // Declare the innards of the Groupers as a new Function and Evaluate
                        Function inner = new Function(ops.GetRange(index + 1, index2 - index - 1), this.parameter);
                        double total_val = inner.Evaluate(this.argval);
                        // Create an Arg_Part representation of the result
                        Arg_Part innerVal = new Arg_Part(total_val.ToString(), Arg_Type.Constant);
                        // Get rid of the Groupers and their innards
                        ops.RemoveRange(index, index2 - index + 1);
                        // Insert the new Arg_Part
                        ops.Insert(index, innerVal);
                    }
              }
              return ops;
        }

        /// <summary>
        /// Finds the next index where the groupers balance out.
        /// TODO: Add verification that we can't just be like 5+(2*x], which would be perfectly okay right now.
        /// </summary>
        /// <param name="ops">The list of argparts to search in</param>
        /// <param name="i">the index of the starting Grouper</param>
        /// <returns></returns>
        private int FindBrother(List<Arg_Part> ops, int i)
        {
            int balance = 0, index = i;
            for (; index < ops.Count; index++)
            {
                if (ops[index].classification == Arg_Type.LGrouper)
                    balance++;
                if (ops[index].classification == Arg_Type.RGrouper)
                    balance--;
                if (balance == 0)
                    return index;
            }
            return -1;
        }

        #endregion
        #endregion

        #region Public
        /// <summary>
        /// The string definition of the function.
        /// </summary>
        public string Definition
        {
            get { return definition; }
            set { definition = value; }
        }

        /// <summary>
        /// The char parameter of the function
        /// </summary>
        public char Parameter
        {
            get { return parameter; }
            //set { parameter = value; }
        }

        /// <summary>
        /// Substitutes necessary values with their respective parameters
        /// </summary>
        /// <param name="argument">The value to evaluate at</param>
        /// <returns>The value of the function</returns>
        public double Evaluate(double argument)
        {
            //double value = Double.NaN;

            return Double.Parse(this.arg_list[0].value);
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

            this.arg_list = Tokenize(this.definition);
            this.ParseImpliedMultiplication(ref this.arg_list);
            this.arg_list = DoConstants(arg_list);
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
