from ._core import DataFrame as _DataFrame


class DataFrame(_DataFrame):
    def __repr__(self) -> str:
            if self.col_count == 0:
                return "Empty DataFrame"

            total_rows = self.row_count
            n_rows = min(5, total_rows)

            # 1. Calculate Widths
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

            # --- TOP BORDER ---
            df_str += "┌" + "┬".join(["─" * (w + 2) for w in max_col_widths]) + "┐\n"

            print("c")
            # --- HEADER ROW ---
            header_parts = [
                self.get_name(i).center(max_col_widths[i]) 
                for i in range(self.col_count)
            ]
            df_str += "│ " + " │ ".join(header_parts) + " │\n"
            print("b")
            # --- DTYPE ROW ---
            dtype_parts = [
                str(self.get_dtype(i)).center(max_col_widths[i])
                for i in range(self.col_count)
            ]
            df_str += "│ " + " │ ".join(dtype_parts) + " │\n"

            # --- SEPARATOR ---
            df_str += "├" + "┼".join(["─" * (w + 2) for w in max_col_widths]) + "┤\n"

            # --- DATA ROWS ---
            for row_idx in range(n_rows):
                row_items = []
                for col_idx in range(self.col_count):
                    # Corrected to get_value
                    val = str(self.get_value(row_idx, col_idx))
                    row_items.append(val.ljust(max_col_widths[col_idx]))

                df_str += "│ " + " │ ".join(row_items) + " │\n"

            # --- BOTTOM BORDER ---
            df_str += "└" + "┴".join(["─" * (w + 2) for w in max_col_widths]) + "┘"

            return df_str