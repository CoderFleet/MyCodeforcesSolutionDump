# Input : line 1 = T; then per case: line A = root name, line B = compact JSON.
# Output: per-case blocks joined by a line `---`, ending with one '\n'.

import sys
import json

class TypeNode:
    def __init__(self, key_name):
        self.key_name = key_name
        self.primitives = set()
        self.has_array = False
        self.array_node = None
        self.has_object = False
        self.object_node = None
        self.present_count = 0

class InterfaceNode:
    def __init__(self, key_name):
        self.key_name = key_name
        self.assigned_name = None
        self.properties = {}
        self.instance_count = 0

class TypeScriptGenerator:
    def __init__(self):
        self.interfaces = []
        self.used_names = set()

    def merge_value(self, type_node, value):
        if value is None:
            type_node.primitives.add('null')
        elif isinstance(value, bool):
            type_node.primitives.add('boolean')
        elif isinstance(value, (int, float)):
            type_node.primitives.add('number')
        elif isinstance(value, str):
            type_node.primitives.add('string')
        elif isinstance(value, list):
            type_node.has_array = True
            if type_node.array_node is None:
                type_node.array_node = TypeNode(type_node.key_name)
            for item in value:
                self.merge_value(type_node.array_node, item)
        elif isinstance(value, dict):
            type_node.has_object = True
            if type_node.object_node is None:
                type_node.object_node = InterfaceNode(type_node.key_name)
            self.merge_object(type_node.object_node, value)

    def merge_object(self, interface_node, obj_data):
        interface_node.instance_count += 1
        for key, val in obj_data.items():
            if key not in interface_node.properties:
                # print(key)
                # print("\n")
                interface_node.properties[key] = TypeNode(key)
            
            property_node = interface_node.properties[key]
            property_node.present_count += 1
            self.merge_value(property_node, val)

    def assign_names(self, interface_node, is_root=False, root_name=""):
        if is_root:
            interface_node.assigned_name = root_name
            self.used_names.add(root_name)
        else:
            base_name = interface_node.key_name[0].upper() + interface_node.key_name[1:]
            candidate = base_name
            suffix = 2
            while candidate in self.used_names:
                # print("-->" + candidate)


                candidate = f"{base_name}{suffix}"
                suffix += 1
                
            interface_node.assigned_name = candidate
            self.used_names.add(candidate)
        
        self.interfaces.append(interface_node)
        for key in sorted(interface_node.properties.keys()):
            property_node = interface_node.properties[key]
            self.traverse_type_node(property_node)

    def traverse_type_node(self, type_node):
        if type_node.has_object and type_node.object_node:
            self.assign_names(type_node.object_node)
        if type_node.has_array and type_node.array_node:
            self.traverse_type_node(type_node.array_node)

    def get_type_string(self, type_node):
        types = set(type_node.primitives)
        if type_node.has_object and type_node.object_node:
            types.add(type_node.object_node.assigned_name)
            
        if type_node.has_array and type_node.array_node:
            array_node = type_node.array_node
            if not array_node.primitives and not array_node.has_object and not array_node.has_array:
                types.add("unknown[]")
            else:
                element_type = self.get_type_string(array_node)
                if " | " in element_type:
                    types.add(f"({element_type})[]")
                else:
                    types.add(f"{element_type}[]")
        # print("tp: ", types)
        return " | ".join(sorted(list(types)))

    def generate(self, root_name, json_text):
        data = json.loads(json_text)
        if not isinstance(data, list):
            return ""
        root_interface = InterfaceNode(root_name)
        for item in data:
            if isinstance(item, dict):
                self.merge_object(root_interface, item)
        self.assign_names(root_interface, is_root=True, root_name=root_name)
        self.interfaces.sort(key=lambda x: x.assigned_name)
        
        output_blocks = []
        for interface in self.interfaces:
            if not interface.properties:
                output_blocks.append(f"export interface {interface.assigned_name} {{}}")
                continue
            lines = [f"export interface {interface.assigned_name} {{"]
            for key in sorted(interface.properties.keys()):
                property_node = interface.properties[key]
                is_optional = "?" if property_node.present_count < interface.instance_count else ""
                type_string = self.get_type_string(property_node)
                lines.append(f"  {key}{is_optional}: {type_string};")
            
            lines.append("}")
            output_blocks.append("\n".join(lines))
            
        return "\n\n".join(output_blocks)
    
def solve(root_name, json_text):
    generator = TypeScriptGenerator()
    return generator.generate(root_name, json_text)

def main():
    lines = sys.stdin.read().split('\n') 
    t = int(lines[0])

    blocks = []
    for i in range(t):
        root_name = lines[1 + 2 * i]
        json_text = lines[2 + 2 * i]
        blocks.append(solve(root_name, json_text))

    sys.stdout.write('\n---\n'.join(blocks) + '\n')

if __name__ == '__main__':
    main()