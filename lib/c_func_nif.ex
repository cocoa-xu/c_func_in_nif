defmodule CFunc.Nif do
  @moduledoc false

  @on_load :load_nif
  def load_nif do
    nif_file = ~c"#{:code.priv_dir(:c_func_in_nif)}/c_nif"

    case :erlang.load_nif(nif_file, 0) do
      :ok -> :ok
      {:error, {:reload, _}} -> :ok
      {:error, reason} -> IO.puts("Failed to load nif: #{reason}")
    end
  end

  def pointer_to_my_add(), do: :erlang.nif_error(:not_loaded)
  def new_struct(_mode, _a, _b), do: :erlang.nif_error(:not_loaded)
  def free_struct(_ptr), do: :erlang.nif_error(:not_loaded)
end
