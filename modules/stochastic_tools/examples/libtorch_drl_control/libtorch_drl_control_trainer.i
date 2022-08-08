[StochasticTools]
[]

[Samplers]
  [dummy]
    type = CartesianProduct
    linear_space_items = '0 0.01 1'
  []
[]

[MultiApps]
  [runner]
    type = SamplerFullSolveMultiApp
    sampler = dummy
    input_files = 'libtorch_drl_control_sub.i'
  []
[]

[Transfers]
  [nn_transfer]
    type = LibtorchNeuralNetControlTransfer
    to_multi_app = runner
    trainer_name = nn_trainer
    control_name = src_control
  []
  [r_transfer]
    type = MultiAppReporterTransfer
    from_multi_app = runner
    to_reporters = 'results/center_temp results/env_temp results/reward results/top_flux '
                   'results/log_prob_top_flux'
    from_reporters = 'T_reporter/center_temp_tend:value T_reporter/env_temp:value T_reporter/reward:value '
                     'T_reporter/top_flux:value T_reporter/log_prob_top_flux:value'
  []
[]

[Trainers]
  [nn_trainer]
    type = LibtorchDRLControlTrainer
    sampler = dummy
    response_reporter = 'results/center_temp results/env_temp'
    control_reporter = 'results/top_flux'
    log_probability_reporter = 'results/log_prob_top_flux'
    reward_reporter = 'results/reward'

    num_epochs = 1000
    update_frequency = 20
    decay_factor = 0.01

    loss_print_frequency = 10

    critic_learning_rate = 0.001
    num_critic_neurons_per_layer = '64 27'

    control_learning_rate = 0.001
    num_control_neurons_per_layer = '64 27'

    # keep consistent with LibtorchNeuralNetControl
    input_timesteps = 2
    response_scaling_factors = '0.03 0.03'
    response_shift_factors = '270 270'
    action_standard_deviations = '0.1'

    standardize_advantage = false

    read_from_file = false
  []
[]

[Reporters]
  [results]
    type = ConstantReporter
    real_vector_names = 'center_temp env_temp reward top_flux log_prob_top_flux'
    real_vector_values = '0; 0; 0; 0; 0;'
    outputs = csv
    execute_on = timestep_begin
  []
  [reward]
    type = DRLRewardReporter
    drl_trainer_name = nn_trainer
  []
[]

[Executioner]
  type = Transient
  num_steps = 400
[]

[Outputs]
  file_base = output/train_out
  csv = true
[]
