/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author seanallred
 */
public class Function {
    private String _definition;
    private char _parameter;

        public enum Arg_Types
    {
        Constant,
        Variable,
        Operator,
        Grouper,
        Unknown,
        Void
    }

    Arg_Types Arg_Type_Of(char c) {
        final String _operators = "+-*/^%!";
        final String _groupers = "()[]{}";
        if (Character.isDigit(c) || c == '.')
            return Arg_Types.Constant;
        if (c == this._parameter)
            return Arg_Types.Variable;
        if (_operators.contains("" + c))
            return Arg_Types.Operator;
        if (_groupers.contains("" + c))
            return Arg_Types.Grouper;
        return Arg_Types.Unknown;
    }
    
    public class Arg_Part {
        public String value;
        public Arg_Types classification;

        public Arg_Part(String value, Arg_Types classification) {
            this.value = value;
            this.classification = classification;
        }

    }

    
    
}
