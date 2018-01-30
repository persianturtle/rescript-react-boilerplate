external unsafeAnyToArray : 'a => array('a) = "%identity";

let first = touchlist => unsafeAnyToArray(touchlist)[0];