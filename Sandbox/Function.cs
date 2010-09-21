﻿using System;
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
        public List<Arg_Part> arg_list = new List<Arg_Part>
        {
            new Arg_Part("", Arg_Types.Void)
        };
        
        #endregion

        #region Public

        public string Definition
        {
            get { return definition; }
            //set { definition = value; }
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

            string arg_buffer = "";
            Arg_Types type_buffer = Arg_Types.Void;
            foreach (char c in this.Definition)
            {
                if (type_buffer == Arg_Types.Void)
                {
                    type_buffer = Arg_Type_Of(c);
                    arg_buffer += c;
                }
                if (type_buffer == Arg_Type_Of(c))
                    arg_buffer += c;
                else
                {
                    Arg_Part buf;
                    buf.value = arg_buffer;
                    buf.classification = type_buffer;

                    arg_list.Add(buf);
                    arg_buffer = "";
                    type_buffer = Arg_Types.Void;
                }

            }
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