[Mesh]
  file = 2blk-conf-2nd.e
[]

[MeshModifiers]
  [slave]
    type = LowerDBlockFromSideset
    sidesets = '101'
    new_block_id = '10001'
    new_block_name = 'slave_lower'
  []
  [master]
    type = LowerDBlockFromSideset
    sidesets = '100'
    new_block_id = '10000'
    new_block_name = 'master_lower'
  []
[]

[Problem]
  kernel_coverage_check = false
[]

[Functions]
  [./exact_sln]
    type = ParsedFunction
    value = x*x+y*y
  [../]
  [./ffn]
    type = ParsedFunction
    value = -4
  [../]
[]

[Variables]
  [./u]
    order = SECOND
    family = LAGRANGE
    block = '1 2'
  [../]

  [./lm]
    order = SECOND
    family = LAGRANGE
    block = slave_lower
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
  [./ffn]
    type = BodyForce
    variable = u
    function = ffn
  [../]
[]

[Constraints]
  [./ced]
    type = EqualValueConstraint
    variable = lm
    master_variable = u
    master_boundary_id = 100
    master_subdomain_id = 10000
    slave_boundary_id = 101
    slave_subdomain_id = 10001
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = '1 2 3 4'
    function = exact_sln
  [../]
[]

[Postprocessors]
  [./l2_error]
    type = ElementL2Error
    variable = u
    function = exact_sln
    block = '1 2'
    execute_on = 'initial timestep_end'
  [../]
[]

[Preconditioning]
  [./fmp]
    type = SMP
    full = true
    solve_type = 'NEWTON'
  [../]
[]

[Executioner]
  type = Steady
  nl_rel_tol = 1e-14
  l_tol = 1e-14
[]

[Outputs]
  exodus = true
[]
