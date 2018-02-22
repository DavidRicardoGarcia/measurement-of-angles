/* Include files */

#include "ArmModel1_sfun.h"
#include "c2_ArmModel1.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ArmModel1_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[10] = { "r", "i", "j", "k", "nargin",
  "nargout", "fi", "theta", "psi", "q" };

/* Function Declarations */
static void initialize_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void initialize_params_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance);
static void enable_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void disable_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance);
static void set_sim_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void sf_gateway_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void mdl_start_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance);
static void initSimStructsc2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_b_q, const char_T *c2_identifier, real_T c2_y[4]);
static void c2_b_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_d_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_ArmModel1, const char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_ArmModel1InstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_ArmModel1InstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_ArmModel1(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_ArmModel1 = 0U;
}

static void initialize_params_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  const mxArray *c2_c_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", *chartInstance->c2_q, 0, 0U, 1U, 0U,
    2, 1, 4), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_ArmModel1;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_hoistedGlobal, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i0;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("q", c2_u, 0)),
                      "q", c2_dv0);
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    (*chartInstance->c2_q)[c2_i0] = c2_dv0[c2_i0];
  }

  chartInstance->c2_is_active_c2_ArmModel1 = c2_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c2_ArmModel1", c2_u, 1)),
    "is_active_c2_ArmModel1");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_ArmModel1(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_b_fi;
  real_T c2_b_theta;
  real_T c2_b_psi;
  uint32_T c2_debug_family_var_map[10];
  real_T c2_r;
  real_T c2_i;
  real_T c2_j;
  real_T c2_k;
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  real_T c2_b_q[4];
  real_T c2_A;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_y;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_b_A;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_c_A;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_c_y;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_d_A;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_d_y;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_e_A;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_e_y;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_f_A;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_f_y;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_g_A;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_g_y;
  real_T c2_bb_x;
  real_T c2_cb_x;
  real_T c2_h_A;
  real_T c2_db_x;
  real_T c2_eb_x;
  real_T c2_h_y;
  real_T c2_fb_x;
  real_T c2_gb_x;
  real_T c2_i_A;
  real_T c2_hb_x;
  real_T c2_ib_x;
  real_T c2_i_y;
  real_T c2_jb_x;
  real_T c2_kb_x;
  real_T c2_j_A;
  real_T c2_lb_x;
  real_T c2_mb_x;
  real_T c2_j_y;
  real_T c2_nb_x;
  real_T c2_ob_x;
  real_T c2_k_A;
  real_T c2_pb_x;
  real_T c2_qb_x;
  real_T c2_k_y;
  real_T c2_rb_x;
  real_T c2_sb_x;
  real_T c2_l_A;
  real_T c2_tb_x;
  real_T c2_ub_x;
  real_T c2_l_y;
  real_T c2_vb_x;
  real_T c2_wb_x;
  real_T c2_m_A;
  real_T c2_xb_x;
  real_T c2_yb_x;
  real_T c2_m_y;
  real_T c2_ac_x;
  real_T c2_bc_x;
  real_T c2_n_A;
  real_T c2_cc_x;
  real_T c2_dc_x;
  real_T c2_n_y;
  real_T c2_ec_x;
  real_T c2_fc_x;
  real_T c2_o_A;
  real_T c2_gc_x;
  real_T c2_hc_x;
  real_T c2_o_y;
  real_T c2_ic_x;
  real_T c2_jc_x;
  real_T c2_p_A;
  real_T c2_kc_x;
  real_T c2_lc_x;
  real_T c2_p_y;
  real_T c2_mc_x;
  real_T c2_nc_x;
  real_T c2_q_A;
  real_T c2_oc_x;
  real_T c2_pc_x;
  real_T c2_q_y;
  real_T c2_qc_x;
  real_T c2_rc_x;
  real_T c2_r_A;
  real_T c2_sc_x;
  real_T c2_tc_x;
  real_T c2_r_y;
  real_T c2_uc_x;
  real_T c2_vc_x;
  real_T c2_s_A;
  real_T c2_wc_x;
  real_T c2_xc_x;
  real_T c2_s_y;
  real_T c2_yc_x;
  real_T c2_ad_x;
  real_T c2_t_A;
  real_T c2_bd_x;
  real_T c2_cd_x;
  real_T c2_t_y;
  real_T c2_dd_x;
  real_T c2_ed_x;
  real_T c2_u_A;
  real_T c2_fd_x;
  real_T c2_gd_x;
  real_T c2_u_y;
  real_T c2_hd_x;
  real_T c2_id_x;
  real_T c2_v_A;
  real_T c2_jd_x;
  real_T c2_kd_x;
  real_T c2_v_y;
  real_T c2_ld_x;
  real_T c2_md_x;
  real_T c2_w_A;
  real_T c2_nd_x;
  real_T c2_od_x;
  real_T c2_w_y;
  real_T c2_pd_x;
  real_T c2_qd_x;
  real_T c2_x_A;
  real_T c2_rd_x;
  real_T c2_sd_x;
  real_T c2_x_y;
  real_T c2_td_x;
  real_T c2_ud_x;
  int32_T c2_i1;
  int32_T c2_i2;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_psi, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_theta, 1U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_fi, 0U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_fi;
  c2_b_hoistedGlobal = *chartInstance->c2_theta;
  c2_c_hoistedGlobal = *chartInstance->c2_psi;
  c2_b_fi = c2_hoistedGlobal;
  c2_b_theta = c2_b_hoistedGlobal;
  c2_b_psi = c2_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_r, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_j, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_fi, 6U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_theta, 7U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_psi, 8U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_b_q, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_A = c2_b_fi;
  c2_x = c2_A;
  c2_b_x = c2_x;
  c2_y = c2_b_x / 2.0;
  c2_c_x = c2_y;
  c2_d_x = c2_c_x;
  c2_d_x = muDoubleScalarCos(c2_d_x);
  c2_b_A = c2_b_theta;
  c2_e_x = c2_b_A;
  c2_f_x = c2_e_x;
  c2_b_y = c2_f_x / 2.0;
  c2_g_x = c2_b_y;
  c2_h_x = c2_g_x;
  c2_h_x = muDoubleScalarCos(c2_h_x);
  c2_c_A = c2_b_psi;
  c2_i_x = c2_c_A;
  c2_j_x = c2_i_x;
  c2_c_y = c2_j_x / 2.0;
  c2_k_x = c2_c_y;
  c2_l_x = c2_k_x;
  c2_l_x = muDoubleScalarCos(c2_l_x);
  c2_d_A = c2_b_fi;
  c2_m_x = c2_d_A;
  c2_n_x = c2_m_x;
  c2_d_y = c2_n_x / 2.0;
  c2_o_x = c2_d_y;
  c2_p_x = c2_o_x;
  c2_p_x = muDoubleScalarSin(c2_p_x);
  c2_e_A = c2_b_theta;
  c2_q_x = c2_e_A;
  c2_r_x = c2_q_x;
  c2_e_y = c2_r_x / 2.0;
  c2_s_x = c2_e_y;
  c2_t_x = c2_s_x;
  c2_t_x = muDoubleScalarSin(c2_t_x);
  c2_f_A = c2_b_psi;
  c2_u_x = c2_f_A;
  c2_v_x = c2_u_x;
  c2_f_y = c2_v_x / 2.0;
  c2_w_x = c2_f_y;
  c2_x_x = c2_w_x;
  c2_x_x = muDoubleScalarSin(c2_x_x);
  c2_r = c2_d_x * c2_h_x * c2_l_x + c2_p_x * c2_t_x * c2_x_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  c2_g_A = c2_b_fi;
  c2_y_x = c2_g_A;
  c2_ab_x = c2_y_x;
  c2_g_y = c2_ab_x / 2.0;
  c2_bb_x = c2_g_y;
  c2_cb_x = c2_bb_x;
  c2_cb_x = muDoubleScalarSin(c2_cb_x);
  c2_h_A = c2_b_theta;
  c2_db_x = c2_h_A;
  c2_eb_x = c2_db_x;
  c2_h_y = c2_eb_x / 2.0;
  c2_fb_x = c2_h_y;
  c2_gb_x = c2_fb_x;
  c2_gb_x = muDoubleScalarCos(c2_gb_x);
  c2_i_A = c2_b_psi;
  c2_hb_x = c2_i_A;
  c2_ib_x = c2_hb_x;
  c2_i_y = c2_ib_x / 2.0;
  c2_jb_x = c2_i_y;
  c2_kb_x = c2_jb_x;
  c2_kb_x = muDoubleScalarCos(c2_kb_x);
  c2_j_A = c2_b_fi;
  c2_lb_x = c2_j_A;
  c2_mb_x = c2_lb_x;
  c2_j_y = c2_mb_x / 2.0;
  c2_nb_x = c2_j_y;
  c2_ob_x = c2_nb_x;
  c2_ob_x = muDoubleScalarCos(c2_ob_x);
  c2_k_A = c2_b_theta;
  c2_pb_x = c2_k_A;
  c2_qb_x = c2_pb_x;
  c2_k_y = c2_qb_x / 2.0;
  c2_rb_x = c2_k_y;
  c2_sb_x = c2_rb_x;
  c2_sb_x = muDoubleScalarSin(c2_sb_x);
  c2_l_A = c2_b_psi;
  c2_tb_x = c2_l_A;
  c2_ub_x = c2_tb_x;
  c2_l_y = c2_ub_x / 2.0;
  c2_vb_x = c2_l_y;
  c2_wb_x = c2_vb_x;
  c2_wb_x = muDoubleScalarSin(c2_wb_x);
  c2_i = c2_cb_x * c2_gb_x * c2_kb_x - c2_ob_x * c2_sb_x * c2_wb_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_m_A = c2_b_fi;
  c2_xb_x = c2_m_A;
  c2_yb_x = c2_xb_x;
  c2_m_y = c2_yb_x / 2.0;
  c2_ac_x = c2_m_y;
  c2_bc_x = c2_ac_x;
  c2_bc_x = muDoubleScalarCos(c2_bc_x);
  c2_n_A = c2_b_theta;
  c2_cc_x = c2_n_A;
  c2_dc_x = c2_cc_x;
  c2_n_y = c2_dc_x / 2.0;
  c2_ec_x = c2_n_y;
  c2_fc_x = c2_ec_x;
  c2_fc_x = muDoubleScalarSin(c2_fc_x);
  c2_o_A = c2_b_psi;
  c2_gc_x = c2_o_A;
  c2_hc_x = c2_gc_x;
  c2_o_y = c2_hc_x / 2.0;
  c2_ic_x = c2_o_y;
  c2_jc_x = c2_ic_x;
  c2_jc_x = muDoubleScalarCos(c2_jc_x);
  c2_p_A = c2_b_fi;
  c2_kc_x = c2_p_A;
  c2_lc_x = c2_kc_x;
  c2_p_y = c2_lc_x / 2.0;
  c2_mc_x = c2_p_y;
  c2_nc_x = c2_mc_x;
  c2_nc_x = muDoubleScalarSin(c2_nc_x);
  c2_q_A = c2_b_theta;
  c2_oc_x = c2_q_A;
  c2_pc_x = c2_oc_x;
  c2_q_y = c2_pc_x / 2.0;
  c2_qc_x = c2_q_y;
  c2_rc_x = c2_qc_x;
  c2_rc_x = muDoubleScalarCos(c2_rc_x);
  c2_r_A = c2_b_psi;
  c2_sc_x = c2_r_A;
  c2_tc_x = c2_sc_x;
  c2_r_y = c2_tc_x / 2.0;
  c2_uc_x = c2_r_y;
  c2_vc_x = c2_uc_x;
  c2_vc_x = muDoubleScalarSin(c2_vc_x);
  c2_j = c2_bc_x * c2_fc_x * c2_jc_x + c2_nc_x * c2_rc_x * c2_vc_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  c2_s_A = c2_b_fi;
  c2_wc_x = c2_s_A;
  c2_xc_x = c2_wc_x;
  c2_s_y = c2_xc_x / 2.0;
  c2_yc_x = c2_s_y;
  c2_ad_x = c2_yc_x;
  c2_ad_x = muDoubleScalarCos(c2_ad_x);
  c2_t_A = c2_b_theta;
  c2_bd_x = c2_t_A;
  c2_cd_x = c2_bd_x;
  c2_t_y = c2_cd_x / 2.0;
  c2_dd_x = c2_t_y;
  c2_ed_x = c2_dd_x;
  c2_ed_x = muDoubleScalarCos(c2_ed_x);
  c2_u_A = c2_b_psi;
  c2_fd_x = c2_u_A;
  c2_gd_x = c2_fd_x;
  c2_u_y = c2_gd_x / 2.0;
  c2_hd_x = c2_u_y;
  c2_id_x = c2_hd_x;
  c2_id_x = muDoubleScalarSin(c2_id_x);
  c2_v_A = c2_b_fi;
  c2_jd_x = c2_v_A;
  c2_kd_x = c2_jd_x;
  c2_v_y = c2_kd_x / 2.0;
  c2_ld_x = c2_v_y;
  c2_md_x = c2_ld_x;
  c2_md_x = muDoubleScalarSin(c2_md_x);
  c2_w_A = c2_b_theta;
  c2_nd_x = c2_w_A;
  c2_od_x = c2_nd_x;
  c2_w_y = c2_od_x / 2.0;
  c2_pd_x = c2_w_y;
  c2_qd_x = c2_pd_x;
  c2_qd_x = muDoubleScalarSin(c2_qd_x);
  c2_x_A = c2_b_psi;
  c2_rd_x = c2_x_A;
  c2_sd_x = c2_rd_x;
  c2_x_y = c2_sd_x / 2.0;
  c2_td_x = c2_x_y;
  c2_ud_x = c2_td_x;
  c2_ud_x = muDoubleScalarCos(c2_ud_x);
  c2_k = c2_ad_x * c2_ed_x * c2_id_x - c2_md_x * c2_qd_x * c2_ud_x;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_b_q[0] = c2_r;
  c2_b_q[1] = c2_i;
  c2_b_q[2] = c2_j;
  c2_b_q[3] = c2_k;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    (*chartInstance->c2_q)[c2_i1] = c2_b_q[c2_i1];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ArmModel1MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c2_i2 = 0; c2_i2 < 4; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_q)[c2_i2], 3U, 1U, 0U,
                          chartInstance->c2_sfEvent, false);
  }
}

static void mdl_start_c2_ArmModel1(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc2_ArmModel1(SFc2_ArmModel1InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)(c2_machineNumber);
  (void)(c2_chartNumber);
  (void)(c2_instanceNumber);
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_i3;
  const mxArray *c2_y = NULL;
  real_T c2_u[4];
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    c2_u[c2_i3] = (*(real_T (*)[4])c2_inData)[c2_i3];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_b_q, const char_T *c2_identifier, real_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_q), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_q);
}

static void c2_b_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv1[4];
  int32_T c2_i4;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
    c2_y[c2_i4] = c2_dv1[c2_i4];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_q;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i5;
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_b_q = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_q), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_q);
  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    (*(real_T (*)[4])c2_outData)[c2_i5] = c2_y[c2_i5];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_ArmModel1_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_d_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i6;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i6, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_ArmModel1, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = (const char *)c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_ArmModel1), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_ArmModel1);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_ArmModel1InstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_ArmModel1InstanceStruct *chartInstance)
{
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_fi = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c2_q = (real_T (*)[4])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_theta = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_psi = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_ArmModel1_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3772127950U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(169119113U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2137425308U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1028670024U);
}

mxArray* sf_c2_ArmModel1_get_post_codegen_info(void);
mxArray *sf_c2_ArmModel1_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("1ZjyDoRGmNu0ciMeTTphJB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_ArmModel1_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_ArmModel1_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_ArmModel1_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_ArmModel1_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_ArmModel1_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_ArmModel1(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"q\",},{M[8],M[0],T\"is_active_c2_ArmModel1\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_ArmModel1_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_ArmModel1InstanceStruct *chartInstance = (SFc2_ArmModel1InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ArmModel1MachineNumber_,
           2,
           1,
           1,
           0,
           4,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_ArmModel1MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ArmModel1MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ArmModel1MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"fi");
          _SFD_SET_DATA_PROPS(1,1,1,0,"theta");
          _SFD_SET_DATA_PROPS(2,1,1,0,"psi");
          _SFD_SET_DATA_PROPS(3,2,0,1,"q");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,483);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 4U;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ArmModel1MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_ArmModel1InstanceStruct *chartInstance = (SFc2_ArmModel1InstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c2_fi);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c2_q);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c2_theta);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c2_psi);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sMBkCyJTQHu9esgQsV3IhwC";
}

static void sf_opaque_initialize_c2_ArmModel1(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_ArmModel1InstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*)
    chartInstanceVar);
  initialize_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_ArmModel1(void *chartInstanceVar)
{
  enable_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_ArmModel1(void *chartInstanceVar)
{
  disable_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_ArmModel1(void *chartInstanceVar)
{
  sf_gateway_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_ArmModel1(SimStruct* S)
{
  return get_sim_state_c2_ArmModel1((SFc2_ArmModel1InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_ArmModel1(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_ArmModel1(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_ArmModel1InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ArmModel1_optimization_info();
    }

    finalize_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_ArmModel1((SFc2_ArmModel1InstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_ArmModel1(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_ArmModel1((SFc2_ArmModel1InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_ArmModel1(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssSetStatesModifiedOnlyInUpdate(S, 1);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ArmModel1_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1495182124U));
  ssSetChecksum1(S,(2878192377U));
  ssSetChecksum2(S,(1872966507U));
  ssSetChecksum3(S,(2685429654U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_ArmModel1(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_ArmModel1(SimStruct *S)
{
  SFc2_ArmModel1InstanceStruct *chartInstance;
  chartInstance = (SFc2_ArmModel1InstanceStruct *)utMalloc(sizeof
    (SFc2_ArmModel1InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_ArmModel1InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_ArmModel1;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_ArmModel1;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_ArmModel1;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_ArmModel1;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_ArmModel1;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_ArmModel1;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_ArmModel1;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_ArmModel1;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_ArmModel1;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_ArmModel1;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_ArmModel1;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_ArmModel1(chartInstance);
}

void c2_ArmModel1_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_ArmModel1(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_ArmModel1(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_ArmModel1(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_ArmModel1_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
