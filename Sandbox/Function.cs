using System;
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
            if (c == '#')
                return Arg_Types.Predefined;
            return Arg_Types.Unknown;
        }
        public struct Arg_Part
        {
            public string value;
            public Arg_Types classification;
            private Operators opType;
            public Arg_Part(string Value, Arg_Types Classification)
            {
                value = Value;
                classification = Classification;
                if (classification != Arg_Types.Operator)
            }
            public Operators getOperatorType() 
            {
                if (classification != Arg_Types.Operator)
                    throw new ArgumentException("To use this function, the Arg_Part must be of type Operator");
                switch (value)
                {
                    case "+": return Operators.ADD;
                    case "-": return Operators.SUBTRACT;
                    case "*": return Operators.MULTIPLY;
                    case "/": return Operators.DIVIDE;
                    case "%": return Operators.MODULO;
                    case "^": return Operators.EXPONENT;
                    case "!": return Operators.FACTORIAL;
                    default:
                        return Operators.NULL;
                }
            }
        };
        // I believe the ICollection is the closest thing to a C# vector
        public List<Arg_Part> arg_list = new List<Arg_Part> { };

        private void Validate()
        {
            this.Definition = this.Definition.Replace(" ", ""); // Keep this in case I remember anything else we should strip
            //this.Definition = this.Definition.Replace("#pi", Math.PI.ToString());
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
                if (((ops[index].classification == Arg_Types.Constant) && (ops[index+1].classification == Arg_Types.Variable)) ||
                    ((ops[index].classification == Arg_Types.Variable) && (ops[index+1].classification == Arg_Types.Constant)))
                    ops.Insert(index + 1, new Arg_Part("*", Arg_Types.Operator));
            }
        }

        /// <summary>
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
                    return new Arg_Part((Double.Parse(one.value) + Double.Parse(two.value)).ToString(), Arg_Types.Constant);
                case Operators.SUBTRACT:
                    return new Arg_Part((Double.Parse(one.value) - Double.Parse(two.value)).ToString(), Arg_Types.Constant);
                case Operators.MULTIPLY:
                    return new Arg_Part((Double.Parse(one.value) * Double.Parse(two.value)).ToString(), Arg_Types.Constant);
                case Operators.DIVIDE:
                    return new Arg_Part((Double.Parse(one.value) / Double.Parse(two.value)).ToString(), Arg_Types.Constant);
                case Operators.MODULO:
                    return new Arg_Part((Double.Parse(one.value) % Double.Parse(two.value)).ToString(), Arg_Types.Constant);
                case Operators.EXPONENT:
                    return new Arg_Part(Math.Pow(Double.Parse(one.value), Double.Parse(two.value)).ToString(), Arg_Types.Constant);
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
            return new Arg_Part((Double.Parse(arg.value)).ToString(), Arg_Types.Constant);
        }


        private void DoConstants(ref List<Arg_Part> ops)
        {
            for (int index = 1; index < ops.Count; index++)
            {
                if (ops[index].classification == Arg_Types.Operator)
                {
                    switch (ops[index].classification)
                    {
                        case Operators.ADD:

                    }
                }
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
            Predefined,
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
            FACTORIAL = '!',
            NULL
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
