from ._core import DataFrame as _DataFrame


class DataFrame(_DataFrame):
    def __repr__(self) -> str:
        """Prints the first five rows of a Dataframe inlcuding the header.

        Example:
            >>> import bonsai
            >>> df = bonsai.DataFrame({"col1": [1, 2, 3, 4, 5], "col2": [True, False, True, True, True]})
            ┌───────────┬────────────┐
            │    col1   │    col2    │
            │ DTYPE_INT │ DTYPE_BOOL │
            ├───────────┼────────────┤
            │ 1         │ True       │
            │ 2         │ False      │
            │ 3         │ True       │
            │ 4         │ True       │
            │ 5         │ True       │
            └───────────┴────────────┘

        Returns:
            str: The Header and the first 5 rows of a DataFrame
        """
        if self.num_columns == 0:
            return "Empty DataFrame"

        total_rows = self.columns[0].size
        n_rows = min(5, total_rows)

        max_col_widths = []
        for col_idx in range(self.num_columns):
            col_name = self.columns[col_idx].name
            dtype_name = str(self.get_dtype(col_idx))
            current_max = max(len(col_name), len(dtype_name))

            for row_idx in range(n_rows):
                val_len = len(str(self.get_item(row_idx, col_idx)))
                if val_len > current_max:
                    current_max = val_len

            max_col_widths.append(current_max)

        df_str = ""

        # --- TOP BORDER ---
        df_str += "┌"
        df_str += "┬".join(["─" * (w + 2) for w in max_col_widths])
        df_str += "┐\n"

        # --- HEADER ROW ---
        header_parts = [
            self.columns[i].name.center(max_col_widths[i])
            for i in range(self.num_columns)
        ]
        df_str += "│ " + " │ ".join(header_parts) + " │\n"

        # --- DTYPE ROW ---
        dtype_parts = [
            str(self.get_dtype(i)).center(max_col_widths[i])
            for i in range(self.num_columns)
        ]
        df_str += "│ " + " │ ".join(dtype_parts) + " │\n"

        # --- SEPARATOR ---
        df_str += "├"
        df_str += "┼".join(["─" * (w + 2) for w in max_col_widths])
        df_str += "┤\n"

        # --- DATA ROWS ---
        for row_idx in range(n_rows):
            row_items = []
            for col_idx in range(self.num_columns):
                val = str(self.get_item(row_idx, col_idx))
                # Center align looks best for tables
                row_items.append(val.ljust(max_col_widths[col_idx]))

            df_str += "│ " + " │ ".join(row_items) + " │\n"

        # --- BOTTOM BORDER ---
        df_str += "└"
        df_str += "┴".join(["─" * (w + 2) for w in max_col_widths])
        df_str += "┘"

        return df_str
