"""
子节点用 dict 实现
"""

class TrieNode:
    def __init__(self):
        self.terminal = False
        self.children = dict()

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node_iter = self.root
        for c in word:
            if c not in node_iter.children:
                node_iter.children[c] = TrieNode()
            node_iter = node_iter.children[c]
        node_iter.terminal = True

    def search(self, word: str) -> bool:
        node_iter = self._find(word)
        return node_iter is not None and node_iter.terminal

    def startsWith(self, prefix: str) -> bool:
        return self._find(prefix) is not None

    def _find(self, prefix):
        node_iter = self.root
        for c in prefix:
            if c not in node_iter.children:
                return None
            node_iter = (node_iter.children)[c]
        return node_iter
