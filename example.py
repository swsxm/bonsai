import bonsai

df = bonsai.DataFrame({"col1": [1, 2, 3, 4, 5], "col2": ["Hi", "Hi", "Hi", "Hi", "Hi"]})
df_new = df.select("col1")
