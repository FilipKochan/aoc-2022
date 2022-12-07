from typing import List, Optional
import sys

SPACE_AVAILABLE = 70_000_000
SPACE_NEEDED = 30_000_000

class Node:
  def __init__(self, name, size=-1) -> None:
    self.name = name
    self.children: List['Node'] = []
    self.size = size
    self.__computed_total_size: Optional[int] = None
  
  def add_child(self, node: 'Node') -> None:
    self.__computed_total_size = None
    self.children.append(node)

  def total_size(self) -> int:
    if not self.__computed_total_size is None:
      return self.__computed_total_size

    if self.size == -1:
      sz = sum([c.total_size() for c in self.children])
      self.__computed_total_size = sz
      return sz

    return self.size

  def to_str(self, depth=0):
    if self.size != -1:
      return f"{' '*2*depth}- {self.name} (file, size={self.size})"

    children_repr: List[str] = []
    for child in self.children:
      children_repr.append(child.to_str(depth + 1))

    return f"{' '*2*depth}- {self.name} (dir)\n" + "\n".join(children_repr)


def record_at(root: Node, path: str, fname: str, fsz: int=-1):
  componetns = list(reversed(path[1:].split("/")))
  current = root

  while componetns and path != "/":
    next_dir = componetns.pop()
    found = False
    for dir in current.children:
      if dir.name == next_dir:
        assert dir.size == -1
        current = dir
        found = True
        break
    if not found:
      tmp = Node(next_dir)
      current.add_child(tmp)
      current = tmp

  if not any([ c.name == fname for c in current.children ]):
    current.add_child(Node(fname, fsz))
  

def parse() -> Node:
  current_path = "/"
  root = Node("/")
  for line in sys.stdin:
    if line[0] == '$':
      args = line[1:].split()
      if args[0] == "cd":
        current_path = new_path(current_path, args[1])
      if args[0] == "ls":
        pass # ignore
    elif line.split()[0] == "dir":
      record_at(root, current_path, line.split()[1])
    else:
      record_at(root, current_path, line.split()[1], int(line.split()[0]))
  return root


def new_path(prev: str, change: str):
  if change == "..":
    if prev == "/":
      return prev
    new = prev.split("/")
    new.pop()
    res = "/".join(new) 
    if not res:
      return "/"
    return res

  if change[0] == "/":
    return change

  delim = "/"
  if prev =="/":
    delim = ""
  return f"{prev}{delim}{change}"

def part1(root: Node) -> int:
  res = 0
  stack = [root]

  while stack:
    cur = stack.pop()
    for c in cur.children:
      if c.size > -1:
        continue
      sz = c.total_size()
      if sz <= 100_000:
        res += sz
      stack.append(c)

  return res

def part2(root: Node) -> int:
  sizes = []
  stack = [root]

  used = root.total_size()

  while stack:
    cur = stack.pop()
    if cur.size == -1:
      sz = cur.total_size()
      if used + SPACE_NEEDED - sz <= SPACE_AVAILABLE:
        sizes.append(sz)
    for c in cur.children:
      stack.append(c)

  sizes.sort()
  return sizes[0]

root = parse()


print(f"part 1: {part1(root)}")
print(f"part 2: {part2(root)}")
