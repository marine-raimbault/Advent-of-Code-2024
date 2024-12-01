defmodule ElixirSolTest do
  use ExUnit.Case
  doctest ElixirSol

  test "greets the world" do
    assert ElixirSol.hello() == :world
  end
end
