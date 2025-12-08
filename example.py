import bonsai

df = bonsai.DataFrame(
    {
        "col1": [1, 2, 3, 4, 5],
        "col2": ["Hi", "Hi", "Hi", "Hi", "Hi"],
        "col3": [1, 2, 3, 4, 5],
    }
)
df_new = df.select(["col1"])
del df_new
df_new_new = df.add("col1", "col3", "col4")
print(df_new_new)
