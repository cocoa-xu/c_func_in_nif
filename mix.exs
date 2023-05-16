defmodule CFuncInNif.MixProject do
  use Mix.Project

  @version "0.1.0"
  @github_url "https://github.com/cocoa-xu/c_func_in_nif"

  def project do
    [
      app: :c_func_in_nif,
      version: @version,
      elixir: "~> 1.10",
      start_permanent: Mix.env() == :prod,
      deps: deps(),
      compilers: [:elixir_make] ++ Mix.compilers(),
      make_precompiler: {:nif, CCPrecompiler},
      make_precompiler_url: "#{@github_url}/releases/download/v#{@version}/@{artefact_filename}",
      make_precompiler_filename: "c_nif"
    ]
  end

  def application do
    [
      extra_applications: [:logger]
    ]
  end

  defp deps do
    [
      # compilation
      {:cc_precompiler, "~> 0.1.0"},
      {:elixir_make, "~> 0.7.0"}
    ]
  end
end
