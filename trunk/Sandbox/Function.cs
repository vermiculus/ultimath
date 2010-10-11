using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sandbox
{
    public class Function
    {
        #region Variable Members

        #region Private

        private string definition;
        private char parameter;


        Arg_Types Arg_Type_Of(char c)
        {
            const string _operators = "+-*/^%!";
            const string _groupers = "()[]{}";

            if (Char.IsDigit(c) || c == '.')
                return Arg_Types.Constant;
            if (c == this.Parameter)
                return Arg_Types.Variable;
            if (_operators.Contains(c))
                return Arg_Types.Operator;
            if (_groupers.Contains(c))
                return Arg_Types.Grouper;
            return Arg_Types.Unknown;
        }
        public struct Arg_Part
        {
            public string value;
            public Arg_Types classification;
            public Arg_Part(string Value, Arg_Types Classification)
            {
                value = Value;
                classification = Classification;
            }
        };
        // I believe the ICollection is the closest thing to a C# vector
        public List<Arg_Part> arg_list = new List<Arg_Part> { };

        private void Validate()
        {
            this.Definition = this.Definition.Replace(" ", ""); // Keep this in case I remember anything else we should strip
        }
        private void Tokenize()//Tokenize_StevensTest
        {
            // Strip whitespace and check for invalid 
            Validate();

            bool isVariable = false; // To check if we should keep adding to the variable string

            for (int index = 0; index < this.definition.Length; index++)
            {
                char c = definition[index];
                Arg_Types type = Arg_Type_Of(c);

                // If its a variable then lets see if we had a variable last time we went through
                if (type == Arg_Types.Constant)
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

                    if (prevArg.classification == Arg_Types.Operator && type == Arg_Types.Operator)
                        throw new InvalidOperationException("Two or more operators were found adjacent to each another: not allowed! PARADOX!");

                    arg_list.Add(buf);
                }
            }
        }

        private void __Tokenize_old()
        {
            string arg_buffer = "";
            Arg_Types type_buffer = Arg_Types.Void;
            foreach (char c in this.Definition)
            {
                if (type_buffer == Arg_Types.Void)
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

                    if (buf.classification == Arg_Types.Operator && buf.value.Length > 1)
                        throw new InvalidOperationException("Two or more operators were found adjacent to each another: not allowed!");

                    arg_list.Add(buf);
                    arg_buffer = c.ToString();
                    type_buffer = Arg_Type_Of(c);
                }
            }
        }

        #region Do Work, Son!

        /// <summary>
        /// An archetype to perform a binary operation (5+4, 8*46, etc)
        /// </summary>
        /// <param name="one">The first operand</param>
        /// <param name="op">The operator</param>
        /// <param name="two">The second operand</param>
        private void DoBinary(Arg_Part one, Operators op, Arg_Part two)
        {
            // must provide validation that it is an BINARY OPERATOR
        }

        /// <summary>
        /// An archetype to perform a unary operation (5!, etc)
        /// </summary>
        /// <param name="arg">The operand</param>
        /// <param name="op">The operater</param>
        private void DoUnary(Arg_Part arg, Operators op)
        {
            // must provide validation that it is an UNARY OPERATOR
        }

        /// <summary>
        /// Status: Complete
        /// Insert implied operators in the arg_list so that 2x becomes 2*x
        /// </summary>
        /// <param name="ops">The collection of Arg_Parts to perform the operation on. This may become obselete as we optimize.</param>
        private void ParseImpliedMultiplication(ref List<Arg_Part> ops)
        {
            for (int index = 0; index < ops.Count-1; index++)
            {
                // if ConstantVariable OR VariableConstant
                // may want to revise so that VariableConstant is parsed as Variable^Constant
                if (((ops[index].classification == Arg_Types.Constant) || (ops[index].classification == Arg_Types.Variable)) &&
                    ((ops[index+1].classification == Arg_Types.Variable) || (ops[index+1].classification == Arg_Types.Constant)))
                    ops.Insert(index + 1, new Arg_Part("*", Arg_Types.Operator));
            }
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
            definition = Def;
            parameter = Param;

            this.Tokenize();
            this.ParseImpliedMultiplication(ref arg_list);
        }

        public double Evaluate(double argument)
        {
            double value = Double.NaN;

            return value;
        }
        #endregion
        #region Groupers
        public enum Arg_Types
        {
            Constant,
            Variable,
            Operator,
            Grouper,
            Unknown,
            Void
        }
        enum Operators
        {
            ADD = '+',
            SUBTRACT = '-',
            MULTIPLY = '*',
            DIVIDE = '/',
            EXPONENT = '^',
            MODULO = '%',
            FACTORIAL = '!'
        }
        enum Groupers
        {
            LPAREN = '(',
            RPAREN = ')',
            LBRACKET = '[',
            RBRACKET = ']',
            LBRACE = '{',
            RBRACE = '}'
        }
        #endregion
    }
}
