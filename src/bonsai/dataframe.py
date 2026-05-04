from ._core import DataFrame as _DataFrame


class DataFrame(_DataFrame):
    def __repr__(self) -> str:
        """Returns a string representation of the DataFrame.

        Example:
            >>> df = DataFrame({"A": [1, 2, 3], "B": [4, 5, 6]})
            >>> print(df)
            ┌─────┬─────┐
            │   A │   B │
            │ int │ int │
            ├─────┼─────┤
            │   1 │   4 │
            │   2 │   5 │
            │   3 │   6 │
            └─────┴─────┘
        """
        if self.col_count == 0:
            return "Empty DataFrame"

        total_rows = self.row_count
        n_rows = min(5, total_rows)

        max_col_widths = []
        for col_idx in range(self.col_count):
            col_name = self.get_name(col_idx)
            dtype_name = str(self.get_dtype(col_idx))
            current_max = max(len(col_name), len(dtype_name))

            for row_idx in range(n_rows):
                val_len = len(str(self.get_value(row_idx, col_idx)))
                if val_len > current_max:
                    current_max = val_len

            max_col_widths.append(current_max)

        df_str = ""

        # top border row
        df_str += "┌" + "┬".join(["─" * (w + 2) for w in max_col_widths]) + "┐\n"

        # header row 
        header_parts = [
            self.get_name(i).center(max_col_widths[i]) 
            for i in range(self.col_count)
        ]
        df_str += "│ " + " │ ".join(header_parts) + " │\n"

        # dtype row 
        dtype_parts = [
            str(self.get_dtype(i)).center(max_col_widths[i])
            for i in range(self.col_count)
        ]
        df_str += "│ " + " │ ".join(dtype_parts) + " │\n"

        # seperator row 
        df_str += "├" + "┼".join(["─" * (w + 2) for w in max_col_widths]) + "┤\n"

        # data rows 
        for row_idx in range(n_rows):
            row_items = []
            for col_idx in range(self.col_count):
                val = str(self.get_value(row_idx, col_idx))
                row_items.append(val.ljust(max_col_widths[col_idx]))

            df_str += "│ " + " │ ".join(row_items) + " │\n"

        # bottem border row 
        df_str += "└" + "┴".join(["─" * (w + 2) for w in max_col_widths]) + "┘"

        return df_str