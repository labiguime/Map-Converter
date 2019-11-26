# Map-Converter
These are rules which are used for the conversion from XML to JSON format:
- Attributes will be treated as regular JSON properties
- Attributes MAY be prefixed with a string to differentiate them from regular XML elements
- Sequences of two or more similar elements will be converted to a JSON array
- Namespaces are completely omitted from the resulting property names
