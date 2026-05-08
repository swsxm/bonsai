from ._core import DataFrame as _DataFrame

class DataFrame(_DataFrame):
    def _pretty_print(self, amount_rows: int, start_at: int = 0) -> str:
        """Generates a formatted ASCII table representation of the DataFrame.
        
        Args:
            amount_rows: The maximum number of rows to include in the table.
            start_at: The row index to begin the slice from.
        """
        if self.col_count == 0:
            return "Empty DataFrame"

        total_rows = self.row_count

        n_rows_to_show = min(amount_rows, total_rows - start_at)
        
        if n_rows_to_show <= 0:
            return f"Empty range (start_at {start_at} >= total rows {total_rows})"

        max_col_widths = []
        for col_idx in range(self.col_count):
            col_name = self.get_name(col_idx)
            dtype_name = str(self.get_dtype(col_idx))
            current_max = max(len(col_name), len(dtype_name))

            for i in range(n_rows_to_show):
                row_idx = start_at + i
                val_str = str(self.get_value(row_idx, col_idx))
                current_max = max(current_max, len(val_str))

            max_col_widths.append(current_max)

        df_str = ""

        # Top border
        df_str += "┌" + "┬".join(["─" * (w + 2) for w in max_col_widths]) + "┐\n"

        # Header
        header_parts = [
            self.get_name(i).center(max_col_widths[i]) 
            for i in range(self.col_count)
        ]
        df_str += "│ " + " │ ".join(header_parts) + " │\n"

        # Dtype
        dtype_parts = [
            str(self.get_dtype(i)).center(max_col_widths[i])
            for i in range(self.col_count)
        ]
        df_str += "│ " + " │ ".join(dtype_parts) + " │\n"

        # Separator
        df_str += "├" + "┼".join(["─" * (w + 2) for w in max_col_widths]) + "┤\n"

        # Data rows
        for i in range(n_rows_to_show):
            row_idx = start_at + i
            row_items = []
            for col_idx in range(self.col_count):
                val = str(self.get_value(row_idx, col_idx))
                row_items.append(val.ljust(max_col_widths[col_idx]))

            df_str += "│ " + " │ ".join(row_items) + " │\n"

        # Bottom border
        df_str += "└" + "┴".join(["─" * (w + 2) for w in max_col_widths]) + "┘"

        # Summary line 
        df_str += f"\nshape: ({self.row_count}, {self.col_count})"

        return df_str

    def __repr__(self) -> str:
        """Default representation showing the first 5 rows."""
        return self._pretty_print(5)
    
    def head(self, amount_rows: int = 5) -> str:
        """Returns a string representation of the first n rows.

        Args:
            amount_rows: The number of rows to display from the top.
        """
        return self._pretty_print(amount_rows, start_at=0)
    
    def tail(self, amount_rows: int = 5) -> str:
        """Returns a string representation of the last n rows.

        Args:
            amount_rows: The number of rows to display from the bottom.
        """
        start_row = max(self.row_count - amount_rows, 0)
        return self._pretty_print(amount_rows, start_at=start_row)